{-# Language BangPatterns #-}

import Control.Arrow
import Control.Monad.State
import qualified Data.Map as M
import Data.Map (Map)
import Data.List (permutations)

newtype City = City String deriving (Ord, Eq, Show)
type CityList = [(City, Int)]
type Edge = (City, City, Int)
type Path = [City]
type EdgeList = [Edge]
type CityMap = Map City CityList

insertEdge :: CityMap -> City -> City -> Int -> CityMap
insertEdge cities c1 c2 dist = foldr (\ (x1, x2) acc -> M.alter (addCityAlter x2 dist) x1 acc) cities [(c1, c2), (c2, c1)]

addCityAlter :: City -> Int -> Maybe CityList -> Maybe CityList
addCityAlter city dist (Just citylist) = Just $ addCity city dist citylist
addCityAlter city dist Nothing = Just $ addCity city dist []

addCity :: City -> Int -> CityList -> CityList
addCity city dist = (:) (city, dist)

initCities :: EdgeList -> CityMap
initCities = foldr (\ (x1, x2, dist) acc -> insertEdge acc x1 x2 dist) M.empty

listEdges :: [String] -> EdgeList
listEdges = map stringToEdge

stringToEdge :: String -> Edge
stringToEdge str = case (words str) of
    [city1Name, "to", city2Name, "=", dist] -> (City city1Name, City city2Name, read dist)
    _ -> undefined

pathDistance :: CityMap -> Path -> Maybe Int
pathDistance = pathDistance' 0
pathDistance' :: Int -> CityMap -> Path -> Maybe Int
pathDistance' x _ [] = Just x
pathDistance' x _ [_] = Just x
pathDistance' x cityMap (c1:c2:cities) = do
    distance <- lookup c2 (M.findWithDefault [] c1 cityMap)
    pathDistance' (x + distance) cityMap (c2:cities)

allDistances :: CityMap -> [(Maybe Int, Path)]
allDistances cityMap = map (pathDistance cityMap &&& id) allPaths
  where
    cities = M.keys cityMap
    allPaths = permutations cities

main = interact $ show . minimum . allDistances . initCities . listEdges . lines
