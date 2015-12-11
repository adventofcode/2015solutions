{-# Language BangPatterns #-}

import Data.List (span)

-- Make Santa run through the floors based on a string.
runFloors :: Integer -> String -> Integer
runFloors !floor [] = floor
runFloors !floor ('(':xs) = runFloors (floor + 1) xs
runFloors !floor (')':xs) = runFloors (floor - 1) xs
runFloors !floor (_:xs) = runFloors floor xs

firstBasement :: Integer -> String -> Maybe Int
firstBasement = firstBasement' 1
  where
    firstBasement' !pos !floor [] = Nothing
    firstBasement' !pos !floor ('(':xs) = firstBasement' (pos + 1) (floor + 1) xs
    firstBasement' !pos !floor (')':xs)
        | floor < 1 = Just pos
        | otherwise = firstBasement' (pos + 1) (floor - 1) xs

main = interact $ show . runFloors 0
