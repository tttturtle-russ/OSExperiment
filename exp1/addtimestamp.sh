#!/bin/bash

# 检查是否提供了路径参数
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

# 获取输入的路径参数
directory=$1

# 检查目标文件夹是否存在
if [ ! -d "$directory" ]; then
    echo "Error: Directory not found."
    exit 1
fi
pattern="^([a-zA-Z0-9_-]+)-20[0-9][0-9]-[0-9][0-9]-[0-9][0-9]-[0-9][0-9]-[0-9][0-9]-[0-9][0-9]\..+$"
# 获取当前日期，格式为YYYYMMDD
date_suffix=$(date +"%Y-%m-%d-%H-%M-%S")
# 遍历目标文件夹中的文件
for file in "$directory"/*; do
    if [ -f "$file" ]; then
        # 获取文件名和扩展名
        filename=$(basename "$file")
        extension="${filename##*.}"
        # 检查文件名中是否已包含日期后缀
        if [[ $filename =~ $pattern ]]; then
            # 如果已经包含日期后缀，则替换现有的后缀
            basename_part="${BASH_REMATCH[1]}"
            new_filename="$basename_part-${date_suffix}.${extension}"
        else
            # 否则，在文件名后追加日期后缀
            new_filename="${filename%.*}-${date_suffix}.${extension}"
        fi
        # 使用mv命令重命名文件

        mv "$file" "$directory/$new_filename"

        echo "Renamed: $filename to $new_filename"
    fi
done

echo "Finished renaming files in $directory"

