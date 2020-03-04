clear
echo "== Made by mburl ==="
echo "=== Welcome to script that checks for norm errors ==="
echo
echo "Files/Folders that will be checked"
ls
echo
ans="*"
bool=0
for file in $ans
do
	if norminette $file | grep "Error" > /dev/null; then
		echo $file "\033[31mX\033[0m"
		bool=1
	else
		echo $file "\033[32mV\033[0m"
	fi
done
if [ $bool -eq 1 ]; then
	echo "\033[31m== Errors found ==\033[0m"
else
	echo "\033[32m== No errors found ==\033[0m"
fi
echo "===== DONE ====="