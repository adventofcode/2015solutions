import Control.Applicative ((<$>), (<*>))
import qualified Data.Map as M
import Control.Monad.State
import Data.Map (Map)
import Data.Bits
import Data.Maybe
import Data.List.Split (splitOn)
import Data.Char (isDigit)
import Data.Word

type Key = String

data Wire b = Binary (b -> b -> b) (Wire b) (Wire b)
            | Unary (b -> b) (Wire b)
            | Var Key
            | Const b

instance Show b => Show (Wire b) where
    show (Binary _ wire1 wire2) = "(" ++ show wire1 ++ ") + (" ++ (show wire2) ++ ")"
    show (Unary _ wire1) = "(" ++ show wire1 ++ ")"
    show (Var key) = "Wire " ++ key
    show (Const x) = show x

type WireMap b = Map Key (Wire b)
type MapState b a = State (WireMap b) a

evalWire :: Wire b -> MapState b (Maybe b)
evalWire (Const x)              = return $ Just x
evalWire (Var key)              = do
    wireMap <- get
    let varWire = (M.lookup key wireMap)
    case varWire of
        Nothing -> return Nothing
        Just wire -> do
            wireValue <- evalWire wire
            modify $ M.insert key (fromMaybe wire (fmap Const wireValue))
            return wireValue
evalWire (Unary f wire)         = do
    x <- evalWire wire
    return $ fmap f x
evalWire (Binary f wire1 wire2) = do
    x <- evalWire wire1
    y <- evalWire wire2
    return $ f <$> x <*> y

evalWireAndAmend :: Key -> MapState b (Maybe b)
evalWireAndAmend = evalWire . Var

findAndReset :: Key -> Key -> MapState b (Maybe b)
findAndReset key resetKey = do
    s0 <- get
    value <- evalWireAndAmend key
    put $ M.insert resetKey (fromMaybe undefined (fmap Const value)) s0
    evalWireAndAmend key

addLineToMap :: (Read b, Bits b, Integral b) => String -> WireMap b -> WireMap b
addLineToMap line wireMap = M.insert rvalue wire wireMap
  where
    [lvalue, rvalue] = fmap strip . splitOn "->" $ line
    lwords = words lvalue
    wire = case (length lwords) of
        1 -> simpleWire lvalue
        2 -> let operator = getUnary (lwords !! 0)
                 wire     = simpleWire (lwords !! 1)
             in Unary operator wire
        3 -> let operator = getBinary (lwords !! 1)
                 wire1    = simpleWire (lwords !! 0)
                 wire2    = simpleWire (lwords !! 2)
             in Binary operator wire1 wire2
        _ -> undefined

simpleWire :: Read b => String -> Wire b
simpleWire [] = undefined
simpleWire str@(x:xs)
    | isDigit x = Const . read $ str
    | otherwise = Var str

getUnary :: Bits b => String -> (b -> b)
getUnary "NOT" = complement
getUnary _ = undefined

getBinary :: (Bits b, Integral b) => String -> (b -> b -> b)
getBinary "AND" = (.&.)
getBinary "OR" = (.|.)
getBinary "LSHIFT" = flip ((flip shiftL) . fromIntegral)
getBinary "RSHIFT" = flip ((flip shiftR) . fromIntegral)
getBinary _ = undefined

strip :: String -> String
strip = lstrip . rstrip
lstrip :: String -> String
lstrip = dropWhile (`elem` " \t")
rstrip :: String -> String
rstrip = reverse . lstrip . reverse

main = interact $ show . evalState (findAndReset "a" "b") . initMap . lines
  where
    initMap :: [String] -> WireMap Word16
    initMap = foldr addLineToMap M.empty
