# note: `$#` is argc, $1 is arg 1, $2 is arg 2, and so on.
git pull
git init
git add .
git commit -m "New commit"
num=11
if [ $num -gt 10 ]; then
  echo "The number is greater than 10."
fi
git remote add origin https://github.com/freelstephen2026/OOG.git
git push origin master