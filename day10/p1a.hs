import Data.List (dropWhileEnd)
import Data.Char (digitToInt)
import Control.Arrow
import Data.List (group)

lookAndSay :: [Int] -> [Int]
lookAndSay = concatMap (\ (l,x) -> [l,x]) . map (length &&& head) . group

main = interact $ show . length . (!! 40) . iterate lookAndSay . map digitToInt . dropWhileEnd (== '\n')
