
-- (c) MP-I (1998/9-2006/7) and CP (2005/6-2022/23)

module NEList where

import Cp

-- (1) Datatype definition -----------------------------------------------------

-- data [a] = a | (:) a ( a) deriving Show

inl = either singl (uncurry (:))

out [a]   = Left a
out (a:x) = Right(a,x)

-- (2) Ana + cata + hylo -------------------------------------------------------

base g f = g -|- (g >< f)

rec f = base id f

cata g = g . rec (cata g) . out   

ana g = inl . (rec (ana g) ) . g

hylo h g = cata h . ana g


-- (3) Examples ----------------------------------------------------------------

concatg ([],ys) = i1 ys
concatg (x:xs,ys) = i2([x],(xs,ys))

concath = either id f
          where f([a],l) = a:l

glast = cata (either id p2)

{--
merge (l,[])                  = l
merge ([],r)                  = r
merge (x:xs,y:ys) | x < y     = x : merge(xs,y:ys)
                  | otherwise = y : merge(x:xs,ys)
--}
mrg (l,[])                  = i1 l
mrg ([],r)                  = i1 r
mrg (x:xs,y:ys) | x < y     = i2(x,(xs,y:ys))
                | otherwise = i2(y,(x:xs,ys))
