{-# Language BangPatterns #-}

import Data.List (findIndices, transpose, sort, group, groupBy, isPrefixOf, isInfixOf, subsequences)
import Data.List.Split (chunksOf)
import Control.Arrow

countNice :: [(String -> Bool)] -> [String] -> Int
countNice functions = length . filter (== True) . map (isNice functions)

isNice :: [(String -> Bool)] -> String -> Bool
isNice functions str = and . map ($ str) $ functions

niceFunctions1 :: [(String -> Bool)]
niceFunctions1 = [hasThreeVowels, hasDouble, not . hasForbiddenLetter]

niceFunctions2 :: [(String -> Bool)]
niceFunctions2 = [nPairs 2, hasPalindrome3]

hasThreeVowels :: String -> Bool
hasThreeVowels = (>= 3) . length . filter (`elem` ['a','e','i','o','u'])

hasDouble :: Eq a => [a] -> Bool
hasDouble = (>= 2) . maximum . map length . group

hasForbiddenLetter :: String -> Bool
hasForbiddenLetter str = or . map ($ str) $ isInfixOf <$> ["ab","cd", "pq", "xy"]

nPairs :: Int -> String -> Bool
nPairs n str = not . null . filter ((>= n) . length . map dropHalf . groupBy adjacent . snd) . map (id &&& (`substrIndices` str)) . uniques . filter (`isInfixOf` str) . filter ((== 2) . length) . subsequences $ str
  where
    differences ((!x):(!y):xs) = y - x : differences (y:xs)
    differences (_:[]) = []
    differences [] = []

    substrIndices :: Eq a => [a] -> [a] -> [Int]
    substrIndices = substrIndices' 0
    substrIndices' :: Eq a => Int -> [a] -> [a] -> [Int]
    substrIndices' _ [] _ = []
    substrIndices' _ _ [] = []
    substrIndices' n substr str@(_:xs)
        | length str < length substr = []
        | substr `isPrefixOf` str = n : substrIndices' (n + 1) substr xs
        | otherwise = substrIndices' (n + 1) substr xs

adjacent !x !y = succ x == y

dropHalf xs = let l = length xs in drop (l `div` 2) xs

hasPalindrome3 :: Eq a => [a] -> Bool
hasPalindrome3 str = or . map (\ str -> str == reverse str) . filter (`isInfixOf` str) . filter ((== 3) . length) . subsequences $ str

uniques :: Eq a => [a] -> [a]
uniques = map head . group

main = interact $ show . countNice niceFunctions2 . lines
