{-# Language BangPatterns #-}

import Data.List (foldl', isPrefixOf)
import qualified Data.Vector as V
import Data.Vector (Vector, (!))
import Data.Char (isDigit)

type Grid a = Vector (Vector a)
type Point = (Int, Int)

startGrid = V.fromList . replicate 1000 $ startRow
startRow = V.fromList . replicate 1000 $ False

analogGrid = V.fromList . replicate 1000 $ analogRow
analogRow = V.fromList . replicate 1000 $ 0

setInGrid :: Point -> Point -> Grid Bool -> Grid Bool
setInGrid (x1, y1) (x2, y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (grid ! y) rowUpdateList | y <- [y1..y2]]
    rowUpdateList = zip [x1..x2] (repeat True)

clearInGrid :: Point -> Point -> Grid Bool -> Grid Bool
clearInGrid (x1, y1) (x2, y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (grid ! y) rowUpdateList | y <- [y1..y2]]
    rowUpdateList = zip [x1..x2] (repeat False)

toggleInGrid :: Point -> Point -> Grid Bool -> Grid Bool
toggleInGrid (x1, y1) (x2, y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (row y) (rowUpdateList y) | y <- [y1..y2]]
    rowUpdateList :: Int -> [(Int, Bool)]
    rowUpdateList y = zip [x1..x2] [not (row y ! x) | x <- [x1..x2]]
    row y = grid ! y

turnOn :: Point -> Point -> Grid Int -> Grid Int
turnOn (x1, y1) (x2, y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (row y) (rowUpdateList y) | y <- [y1..y2]]
    rowUpdateList :: Int -> [(Int, Int)]
    rowUpdateList y = zip [x1..x2] [(row y ! x) + 1 | x <- [x1..x2]]
    row y = grid ! y

turnOff :: Point -> Point -> Grid Int -> Grid Int
turnOff (!x1, !y1) (!x2, !y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (row y) (rowUpdateList y) | y <- [y1..y2]]
    rowUpdateList :: Int -> [(Int, Int)]
    rowUpdateList y = zip [x1..x2] [max 0 ((row y ! x) - 1) | x <- [x1..x2]]
    row y = grid ! y

toggle :: Point -> Point -> Grid Int -> Grid Int
toggle (x1, y1) (x2, y2) grid = V.unsafeUpd grid updateList
  where
    updateList = zip [y1..y2] [V.unsafeUpd (row y) (rowUpdateList y) | y <- [y1..y2]]
    rowUpdateList :: Int -> [(Int, Int)]
    rowUpdateList y = zip [x1..x2] [(row y ! x) + 2 | x <- [x1..x2]]
    row y = grid ! y

parsePoint :: String -> Point
parsePoint str = (x, y)
  where
    (x, y) = (read xString, read . drop 1 $ yString)
    (xString, yString) = break (== ',') str

parseCommand1 :: Grid Bool -> String -> Grid Bool
parseCommand1 grid command
    | "turn on" `isPrefixOf` command = setInGrid p1 p2 grid
    | "turn off" `isPrefixOf` command = clearInGrid p1 p2 grid
    | "toggle" `isPrefixOf` command = toggleInGrid p1 p2 grid
    | otherwise = startGrid
  where
    (_, pointString) = break isDigit command
    [p1String, _, p2String] = words pointString
    (p1, p2) = (parsePoint p1String, parsePoint p2String)

parseCommand2 :: Grid Int -> String -> Grid Int
parseCommand2 grid command
    | "turn on" `isPrefixOf` command = turnOn p1 p2 grid
    | "turn off" `isPrefixOf` command = turnOff p1 p2 grid
    | "toggle" `isPrefixOf` command = toggle p1 p2 grid
    | otherwise = analogGrid
  where
    (_, pointString) = break isDigit command
    [p1String, _, p2String] = words pointString
    (p1, p2) = (parsePoint p1String, parsePoint p2String)

parseCommandList1 :: [String] -> Grid Bool
parseCommandList1 = foldl' parseCommand1 startGrid

parseCommandList2 :: [String] -> Grid Int
parseCommandList2 = foldl' parseCommand2 analogGrid

countLit :: Grid Bool -> Int
countLit = V.foldl' (\ acc x -> if x then acc + 1 else acc) 0 . V.concat . V.toList

countAnalog :: Grid Int -> Integer
countAnalog = V.sum . fmap toInteger . V.concat . V.toList

main = interact $ show . countAnalog . parseCommandList2 . lines
