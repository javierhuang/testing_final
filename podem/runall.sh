cases=("c1355" "c17" "c1908" "c2670" "c3540" "c432" "c499" "c5315" "c6288" "c7552" "c880")
N=10

for i in $(seq 0 $N); do
  echo ""
  echo "running ${cases[$i]}"
  ./atpg -ndet 8 -tdfatpg -compression ../sample_circuits/${cases[$i]}.ckt > pat/${cases[$i]}.pat
  ../ref/golden_tdfsim -ndet 8 -tdfsim pat/${cases[$i]}.pat ../sample_circuits/${cases[$i]}.ckt
done
