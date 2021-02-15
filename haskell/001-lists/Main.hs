module Main where

import LinkedList as LL

test :: Maybe Int -> Maybe Int -> String
test ex act = if ex == act then "Success" else "Fail: Expected " ++ show ex ++ ", Found " ++ show act


main :: IO ()
main = do
    let list = Node 3 . Node 5 . Node 7 . Node 1 . Node 4 $ Null
    putStrLn . test (Just 3) $ LL.get list 0
    putStrLn . test (Just 5) $ LL.get list 1
    putStrLn . test (Just 7) $ LL.get list 2
    putStrLn . test (Just 1) $ LL.get list 3
    putStrLn . test (Just 4) $ LL.get list 4
    putStrLn . test Nothing $ LL.get list 1000
