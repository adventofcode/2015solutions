import Data.Char (isDigit)
import Data.List (sort)

wrappingPaper :: (Int, Int, Int) -> Int
wrappingPaper dim = areaOfBox dim + areaOfSmallestSide dim

areaOfBox :: (Int, Int, Int) -> Int
areaOfBox (l, w, h) = 2 * (sum . map areaOfSide $ [(l, w), (w, h), (l, h)])

areaOfSmallestSide :: (Int, Int, Int) -> Int
areaOfSmallestSide (l, w, h) = minimum . map areaOfSide $ [(l, w), (w, h), (l, h)]

areaOfSide :: (Int, Int) -> Int
areaOfSide (l, w) = l * w

ribbon :: (Int, Int, Int) -> Int
ribbon dim = ribbonAround dim + ribbonBow dim

ribbonAround :: (Int, Int, Int) -> Int
ribbonAround dim = sum . map (* 2) . minimumSides $ dim

ribbonBow :: (Int, Int, Int) -> Int
ribbonBow = volume

minimumSides :: (Int, Int, Int) -> [Int]
minimumSides (l, w, h) = take 2 . sort $ [l, w, h]

volume :: (Int, Int, Int) -> Int
volume (l, w, h) = l * w * h

dimToTuple :: String -> (Int, Int, Int)
dimToTuple = result
  where
    result dim
        | length (splitDimension dim) /= 3 = (0,0,0)
        | otherwise = resultingTuple dim
    splitDimension = splitAll 'x'
    intList dim = map (read . filter isDigit) $ splitDimension dim
    resultingTuple dim = case intList dim of
        [first, second, third] -> (first, second, third)

splitAll :: Eq a => a -> [a] -> [[a]]
splitAll _ [] = [[]]
splitAll delim (x:xs)
    | x == delim = [] : splitAll delim xs
    | otherwise = (x:headList) : tailLists
  where
    (headList:tailLists) = splitAll delim xs

main = interact $ show . sum . map (wrappingPaper . dimToTuple) . lines
