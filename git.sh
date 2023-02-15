# note: `$#` is argc - 1, $1 is arg 1, $2 is arg 2, and so on.
argc=$# - 1
num=1
git pull
git init
git add .
git commit -m "New commit"
num=11
printf "argc = %d" $#
if [ $num -gt $argc ]; then
    echo hifdsafdsafahgtjywjywwkyawsk6yasjk6ysj6ysjkysrjykysrysjy6ts
fi
git remote add origin https://github.com/freelstephen2026/OOG.git
git push origin master