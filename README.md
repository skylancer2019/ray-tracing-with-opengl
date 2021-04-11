# ray-tracing-with-opengl
## 运行环境
Visual Studio nupengl core
## 实现功能
为了生成在三维计算机图形环境中的可见图像，光线跟踪是一个比光线投射或者扫描线渲染更加逼真的实现方法。这种方法通过逆向跟踪与假想的照相机镜头相交的光路进行工作，当光线与场景中的物体或者媒介相交的时候，计算光线的反射、折射以及吸收，从而得到接近真实的渲染结果。

支持设置一个光源，生成多个表面性质不同，大小不同的球体。对物体表面的漫反射和镜面反射进行了光线追踪，能够生成镜面上的高光。对每一个像素点射出的光线的方向，通过一个随机数完成同一像素点的ray tracing,之后对每个ray tracing的结果进行平均，得到该像素点的颜色，完成antialiasing。支持有光源和五光源的情况。
## 实现效果
无光源情况：

![image](https://github.com/skylancer2019/ray-tracing-with-opengl/blob/main/pic/nolight1.png)

![image](https://github.com/skylancer2019/ray-tracing-with-opengl/blob/main/pic/nolight2.png)

有光源情况：

![image](https://github.com/skylancer2019/ray-tracing-with-opengl/blob/main/pic/light1.png)

![image](https://github.com/skylancer2019/ray-tracing-with-opengl/blob/main/pic/ligh2.png)
