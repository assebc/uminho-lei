module Task7 where 

import Cp 
import Nat


rep a = cataNat (either (nil) (a:))

f = p2 . aux where aux = for (split (succ . p1) (mul)) (1,1)

map_mult = either (const 1) (mul)

reverse_list = either (nil) (conc . swap . (singl >< id) )

concat_list = either (nil) (conc)

sumprod a = (a*) . sum