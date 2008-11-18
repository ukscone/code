module Test
    where

listnum n [] = []
listnum 0 (x:xs) = x
listnum n (x:xs) = listnum n-1 xs
