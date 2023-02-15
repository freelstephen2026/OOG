# note: `$#` is argc, $1 is arg 1, $2 is arg 2, and so on.
git pull
git init
git add .
git commit -m "New commit"
num=11
printf "argc = %d" $#
if [ $# -gt 1 ]; then echo 9999999999999999999999999
fi
git remote add origin https://github.com/freelstephen2026/OOG.git
git push origin master