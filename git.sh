# note: `$#` is argc - 1, $1 is arg 1, $2 is arg 2, and so on.
# argc=$# - 1
echo executing line 1
num=1
echo executing line 2
git pull
echo executing line 3
git init
echo executing line 4
git add .
echo executing line 5
git commit -m "New commit"
echo executing line 6
num=11
echo executing line 7
printf "%c%c = %d" $ '#' $#
if [ $# -eq 0 ]; then
    echo expected arg after `./git.sh`
fi
echo executing line 8
git remote add origin https://github.com/freelstephen2026/OOG.git
echo executing line 9
git push origin master