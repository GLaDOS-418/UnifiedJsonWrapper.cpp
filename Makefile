PROJECT_NAME=UnifiedJsonWrapperApp
CC=clang
CXX=clang++

# define docker names
IMAGE_NAME=cppdev
IMAGE_TAG=latest
CONTAINER_NAME=${IMAGE_NAME}_container

# cmake build directory
BUILD_DIR=build

# cmake build type
BUILD_TYPE=Debug

# Define the container home directory variable
CONTAINER_HOME_DIR=/home/${PROJECT_NAME}

.PHONY: build clean rebuild test testprint package run deepclean terminal image format

format:
	git ls-files -cmo --exclude-standard | grep -iE '\.(c|cc|cpp|cxx|txx|h|hpp|tpp)$$' | xargs clang-format -i
package:
	/bin/rm -r build 2 &>/dev/null
	mkdir -p ${BUILD_DIR}
	conan install . \
		--output-folder=${BUILD_DIR} \
		--build=missing \
		--profile:build=conan.profile \
		--profile:host=conan.profile

configure:
	cmake -S . -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
	-DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} \
	-DCMAKE_TOOLCHAIN_FILE=${BUILD_DIR}/conan_toolchain.cmake

build: configure
	cmake --build ${BUILD_DIR}

clean:
	/bin/rm -rf ${BUILD_DIR}

deepclean: clean
	conan remove -c "*"

rebuild: clean  package configure build
	
test:
	cd ${BUILD_DIR} && ctest -C ${BUILD_TYPE} && cd ..

testprint:
	cd ${BUILD_DIR} && \
		ctest --rerun-failed --output-on-failure -C ${BUILD_TYPE} && cd ..

run: check_project_name check_project_exists
	./${BUILD_DIR}/${PROJECT_NAME}

check_project_name:
	@if [ -z "${PROJECT_NAME}" ]; then \
		echo "Error: PROJECT_NAME is empty. Set a valid project name."; \
		exit 1; \
	fi
check_project_exists:
	@if [ ! -e ./${BUILD_DIR}/${PROJECT_NAME} ]; then \
		echo "Error: ${PROJECT_NAME} executable not found. Run 'make build' first."; \
		exit 1; \
	fi
image:
	docker build -f ./.devcontainer/Dockerfile \
		--tag=${IMAGE_NAME}:${IMAGE_TAG} .

terminal:
	if [ $$(docker ps -aq -f name=${CONTAINER_NAME}) ]; then \
		docker start ${CONTAINER_NAME} || true; \
		docker exec -it ${CONTAINER_NAME} /bin/bash; \
	else \
		docker run --net=host -it \
			--name ${CONTAINER_NAME} \
			-v ${PWD}:${CONTAINER_HOME_DIR} \
 			-u $(id -u):$(id -g) \
			-w ${CONTAINER_HOME_DIR} \
			${IMAGE_NAME}:${IMAGE_TAG}; \
	fi
