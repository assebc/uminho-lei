/* Objective function */
min: 1 xka + 15 xkb + 2 xkc + 4 xkd + 11 xkf + 9 xkg + 9 xkh + 9 xki + 10 xkj +
6 xbg +
5 xca + 11 xcb + 6 xcg +
6 xda + 14 xdb + 8 xdf + 8 xdg + 11 xdj
5 xfg +
5 xha + 11 xhb + 0 xhc + 10 xhf + 10 xhg + 6 xhj
0 xia + 13 xib + 5 xic + 10 xif + 7 xig + 5 xih + 7 xij
7 xja + 4 xjb + 5 xjg +
2 xak' + 16 xbk' + 3 xck' + 5 xdk' + 12 xfk' + 10 xgk' + 10 xhk' + 10 xik' + 11 xjk';

/* Variable bounds */
xka + xca + xda + xha + xia + xja = 1;
xak' = 1;
xkb + xcb + xdb + xhb + xib + xjb = 1;
xbg + xbk' = 1;
xkc + xhc + xic = 1;
xca + xcb + xcg + xck' = 1;
xkd = 1;
xda + xdb + xdf + xdg + xdj + xdk' = 1;
xkf + xdf + xhf + xif = 1;
xfg + xfk' = 1;
xkg + xcg + xdg + xhg + xig + xjg = 1;
xgk' = 1;
xkh + xgh + xih = 1;
xha + xhb + xhc + xhf + xhg + xhj + xhk' = 1;
xki = 1;
xia + xib + xic + xif + xig + xih + xij + xik' = 1;
xkj + xdj + xhj + xij + xjg = 1;
xja + xjb + xjg + xjk' = 1;
