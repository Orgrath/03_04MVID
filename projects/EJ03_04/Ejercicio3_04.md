El triangulo mostrado al enviar los vertices como color al fragment Shader, hace quer este ponga ese color en cada uno de ellos, 
dejando el vertice supèrior en verde (0.0R, 0.5G, 0.0B) el derecho en rojo (0.5R, -0.5G, 0.0B) y el izquierdo en negro (-0.5R, -0.5G, 0.0B).
Cabe destacar los valores negativos, que aparentemente paracen aumentar la influencia de quitar color en las zonas mas cercanas al vertice superior como derecho.
Sabiendo que entre el vertex shader y el fragment shader opengl ejecuta el rasterizador que calcula la cantidad de pixels que hay entre los puntos del triangulo 
formado por los vertices y el tamaño en pixels de la ventana donde se visualizará.
Esto hace que el fragment shader se ejecute por cada uno de esos pixeles rellenando con los valores que tiene cada pixel hasta llegar al otro.
Esta interpolación es lineal generando una secuencia que va del valor R G y B de cada vertice hasta el siguiente.
Esto motiva que en esta ejecución el color negro sea predominante yua que los valores negativos no contienen color(negro).

Esto crea un degradado lineal del valor RGB de cada vertice al siguiente adjudicando un valor calculado entre los pixeles que hay entre cada vertice y su correspondiente
valor RGB obtenido igual del rango entre vertices.