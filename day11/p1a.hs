{-# Language BangPatterns #-}

import Data.Function (fix)
import Data.Char (isSpace)
import Data.List (groupBy, group, isPrefixOf, tails)
import Control.Arrow
import Debug.Trace

stepPassword :: String -> String
stepPassword [] = []
stepPassword (x:xs)
    | x == 'z' = 'a' : stepPassword xs
    | otherwise = succ x : xs

validPassword :: [(String -> Bool)] -> String -> Bool
validPassword functions str = and . map ($ str) $ functions

nextPassword :: [(String -> Bool)] -> String -> String
nextPassword functions = head . filter (validPassword functions) . map reverse . iterate stepPassword . stepPassword . reverse

validFunctions1 :: [(String -> Bool)]
validFunctions1 = [straight, not . containsForbidden, nPairs 2]

straight :: String -> Bool
straight = or . map isStraight . windows 3
  where
    isStraight [_] = True
    isStraight [] = True
    isStraight (x:y:xs)
        | y == succ x = isStraight (y:xs)
        | otherwise = False

containsForbidden :: String -> Bool
containsForbidden str = and . map ($ str) $ [('i' `elem`), ('o' `elem`), ('l' `elem`)]

nPairs :: Int -> String -> Bool
nPairs n = (>= 2) . length . filter ((>= 2) . length) . splitLarge n . group
  where
    splitLarge :: Show a => Int -> [[a]] -> [[a]]
    splitLarge n list = concat . fix (splitLarge' n) . map (: []) $ list
    splitLarge' :: Show a => Int -> ([[[a]]] -> [[[a]]]) -> [[[a]]] -> [[[a]]]
    splitLarge' n rec listOfLists = if all (all ((<= n) . length)) listOfLists
                                    then listOfLists
                                    else rec . map ($ concat listOfLists) $ [filter (not . null) . map (take n), filter (not . null) . map (drop n)]

-- Modified from pavolzetor's solution.
windows :: Int -> [a] -> [[a]]
windows n = filter (\x -> length x == n) . map (take n) . tails

strip :: String -> String
strip = rstrip . lstrip
  where
    lstrip = dropWhile isSpace
    rstrip = reverse . lstrip . reverse

main = interact $ (!! 1) . iterate (nextPassword validFunctions1) . strip
