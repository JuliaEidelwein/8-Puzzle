ulimit -t 30
ulimit -v 8000000
while read -r LINE; do     ./main -astar $LINE; done < instances/15puzzle_instances.txt

