#!/usr/bin/zsh

# Loop through folder1 to folder10
for i in $(seq 1 10); do
    dir_name="folder${i}"

    # Check if the directory exists
    if [ -d "$dir_name" ]; then
        # Remove the directory and its contents
        rm -rf "$dir_name"
        echo "Deleted $dir_name"
    else
        echo "$dir_name does not exist, skipping."
    fi
done

echo "Cleanup completed."
