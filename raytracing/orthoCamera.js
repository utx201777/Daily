/*
orthoCamera
*/

orthoCamera = function(eye,front,up,width,height)
{
	this.eye = eye;		// 相机位置
	this.front = front;	// 前方向
	this.up = up;		// 上方向
	this.width = width;
	this.height = height;
};

orthoCamera.prototype = 
{
	initialize:function(){
		this.right = this.up.cross(this.front);	// 获得右向量		
	},

	generateRay:function(x,y){
		var r = this.right.multiply(this.width*(x-0.5));
		var u = this.up.multiply(this.height*(y-0.5));
		return new Ray3(this.eye.add(r).add(u),this.front);
	}
};