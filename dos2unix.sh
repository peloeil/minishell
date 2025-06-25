#!/usr/bin/env bash

while IFS= read -r -d '' file; do
	dos2unix "$file"
done < <(find . -type f -print0)
