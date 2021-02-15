module LinkedList where

data Node a = Null | Node a (Node a)

get :: Node a -> Int -> Maybe a
get Null _          = Nothing
get (Node val _) 0  = Just val
get (Node _ next) i = get next (i - 1)
