{-# Language BangPatterns #-}

import Data.Char (isSpace)
import qualified Data.ByteString.Lazy.Char8 as B

countEscape :: String -> Int
countEscape = countEscape' 2
countEscape' :: Int -> String -> Int
countEscape' !x ('\\':'x':_:_:xs) = countEscape' (x + 3) xs
countEscape' !x ('\\':'\\':xs) = countEscape' (x + 1) xs
countEscape' !x ('\\':'"':xs) = countEscape' (x + 1) xs
countEscape' !x (_:xs) = countEscape' x xs
countEscape' !x [] = x

showDifference :: String -> Int
showDifference str = (length . show $ str) - length str

main = interact $ show . sum . fmap showDifference . lines
