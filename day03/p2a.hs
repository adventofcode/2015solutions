{-# Language BangPatterns #-}

import Data.List (group, scanl, sort, transpose)
import Data.List.Split (chunksOf)

housesWithGroup :: Int -> String -> Int
housesWithGroup n = length . uniques . concat . map movePath . everyN n

housesHit :: String -> Int
housesHit = length . uniques . movePath

movePath :: String -> [(Int, Int)]
movePath = scanl move (0, 0)

move :: (Int, Int) -> Char -> (Int, Int)
move (!x, !y) '<' = (x - 1, y)
move (!x, !y) '>' = (x + 1, y)
move (!x, !y) '^' = (x, y - 1)
move (!x, !y) 'v' = (x, y + 1)
move (!x, !y) _ = (x, y)

everyN :: Int -> [a] -> [[a]]
everyN n = transpose . chunksOf n

uniques :: (Eq a, Ord a) => [a] -> [a]
uniques = map head . group . sort

main = interact $ show . housesWithGroup 2
