sh configure.sh
sh compile.sh
sh murge.sh a.out $1
cp a.out $2
rm -f a.out
