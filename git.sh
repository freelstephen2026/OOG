# note: `$#` is argc - 1, $1 is arg 1, $2 is arg 2, and so on.
# argc=$# - 1
git pull
git init
git add .
git commit -m "Fixed the issue with my::GL::vertices::objectClass::translate(float, float) changing the total amount of floating point numbers to 4"
# commented out code didn't work:
# ```printf "%c%c = %d" '$' '#' $#
# if [ $# -eq 0 ]; then
#     echo expected arg after `./git.sh`
# fi````
echo executing line 8
git remote add origin https://github.com/freelstephen2026/OOG.git
echo executing line 9
git push origin master