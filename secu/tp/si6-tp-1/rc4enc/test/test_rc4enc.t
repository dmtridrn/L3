Test 1
  $ printf "Plaintext" | rc4enc "Key" | hexdump -C
  00000000  bb f3 16 e8 d9 40 af 0a  d3                       |.....@...|
  00000009

Test 2
  $ printf "Attack at dawn" | rc4enc "Secret" | hexdump -C
  00000000  45 a0 1f 64 5f c3 5b 38  35 52 54 4b 9b f5        |E..d_.[85RTK..|
  0000000e
