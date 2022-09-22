mylength :: [a] -> Integer
mylength [] = 0
mylength (x:xs) = 1 + mylength xs

myreverse :: [a] -> [a]
myreverse [] = []
myreverse (x:xs) = myreverse xs ++ [x]

calls :: Eq a => a -> [a] -> [a]
calls c l = take 10 (c : filter(/=c) l)

myuncurry :: (a->b->c) -> (a,b) -> c
myuncurry f = \(x,y) -> f x y

mycurry :: ((a,b) -> c) -> a -> b -> c
mycurry f = \x y -> f (x, y)

myflip :: (a->b->c) -> b -> a -> c
myflip f = \x y -> f y x