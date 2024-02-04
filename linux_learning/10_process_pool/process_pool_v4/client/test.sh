#!/usr/bin/zsh

# Define the number of directories
num_folders=10

# Loop to create directories, copy client.out, and run it
for i in $(seq 1 $num_folders); do
    # Create directory
    dir_name="folder${i}"
    mkdir -p "$dir_name"

    # Copy the client.out file into the new directory
    cp client.out "$dir_name"

    # Change directory and run client.out in background
    (cd "$dir_name" && ./client.out 127.0.0.1 12123 &) 

    echo "Started client.out in $dir_name"
done

# Wait for all background processes to finish
wait

echo "All client.out instances have finished."
