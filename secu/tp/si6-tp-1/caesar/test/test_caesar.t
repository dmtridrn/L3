Test 1
  $ printf "abc def" | caesar -e $(printf "\000")
  abc def

Test 2
  $ printf "abc def" | caesar -e $(printf "\005")
  fgh%ijk

Test 3
  $ printf "\276\225\335\326\351\332\225\302\344\343\331\326\356\350\243" | caesar -d $(printf "\165")
  I hate Mondays.

Test 4
  $ printf "\252\311\311\310\204\321\311\204\320\305\327\305\313\322\305\205" | caesar -e $(printf "\234")
  Feed me lasagna!
