ulimit -v 4000000
while read -r LINE; do     ./main -bfs $LINE; done < instances/8puzzle_instances.txt
echo ""
while read -r LINE; do     ./main -idfs $LINE; done < instances/8puzzle_instances.txt
echo ""
while read -r LINE; do     ./main -astar $LINE; done < instances/8puzzle_instances.txt
echo ""
while read -r LINE; do     ./main -idastar $LINE; done < instances/8puzzle_instances.txt
echo ""
while read -r LINE; do     ./main -gbfs $LINE; done < instances/8puzzle_instances.txt
