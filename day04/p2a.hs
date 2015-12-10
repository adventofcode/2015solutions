{-# Language BangPatterns #-}

import Data.Digest.Pure.MD5 (md5)
import qualified Data.ByteString.Lazy.Char8 as B
import Control.Arrow

pairsWithNZeroes :: Int -> String -> [(String, String)]
pairsWithNZeroes n = filter (startsWithNZeroes n . snd). map md5Pair . allInputs

md5Pair :: String -> (String, String)
md5Pair = (id &&& show . md5 . B.pack)

allInputs :: String -> [String]
allInputs input = map ((++) input . show) [1..]

startsWithNZeroes :: Int -> String -> Bool
startsWithNZeroes n = all (== '0') . take n

main = interact $ fst . head . pairsWithNZeroes 6 . head . lines
