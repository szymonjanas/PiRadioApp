FROM piotrlewandowski/cpp-gstreamer-go-zeromq-build-base:0.1.0

# Set the working directory
WORKDIR /mnt

# Copy files from the host to current directory
COPY CMakeLists.txt /mnt
COPY database.txt /mnt
COPY sources /mnt/sources
COPY server /mnt/server

# Build the application with cmake
RUN mkdir build && cd build && cmake .. && make

# Set the working directory to build folder
WORKDIR build

EXPOSE 8080

# Run the application
CMD ["./PiRadioApp"]
