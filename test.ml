open Mlwrapper

type position = {
  x: float;
  y: float
}

type polar = {
  r: float;
  theta: float
}

let norm2 a b =
  sqrt( (a.x -. b.x) ** 2. +. (a.y -. b.y) ** 2.)

let norm1 a b =
  abs_float( a.x -. b.x ) +. abs_float( a.y -. b.y )

let norm2_p a b =
  sqrt( a.r ** 2. +. b.r ** 2. -. 2. *. a.r *. b.r *. cos(a.theta -. b.theta) )

let _ =
  let a = {x = 2.; y = 4.} in
  let b = {x = 1.; y = -3.} in
  let c = {r = 1.; theta = 0. } in
  let d = {r = 1.; theta = acos(0.) } in
  test a b norm2;
  test a b norm1;
  test c d norm2_p

