# Mess with the date:
date -s "16 May 2019 10:00:00"
for i in {0..100}
do
    echo "==================== $i seconds ===================="
    date 
    ntpstat
    ntptest
    ntpq -p
    sleep 1
done
