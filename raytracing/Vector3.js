Vector3 = function(x, y, z) { this.x = x; this.y = y; this.z = z; };
// 基础向量操作

Vector3.prototype = {
    // 拷贝一个向量
    copy : function() { return new Vector3(this.x, this.y, this.z); },
    // 获取一个模长
    length : function() { return Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z); },
    // 模长的平方
    sqrLength : function() { return this.x * this.x + this.y * this.y + this.z * this.z; },
    // 向量的归一化操作
    normalize : function() { var inv = 1/this.length(); return new Vector3(this.x * inv, this.y * inv, this.z * inv); },
    // 取反操作
    negate : function() { return new Vector3(-this.x, -this.y, -this.z); },
    // 向量相加操作
    add : function(v) { return new Vector3(this.x + v.x, this.y + v.y, this.z + v.z); },
    // 向量相减操作
    subtract : function(v) { return new Vector3(this.x - v.x, this.y - v.y, this.z - v.z); },
    // 向量的数乘
    multiply : function(f) { return new Vector3(this.x * f, this.y * f, this.z * f); },
    // 向量除以一个实数
    divide : function(f) { var invf = 1/f; return new Vector3(this.x * invf, this.y * invf, this.z * invf); },
    // 向量的点乘
    dot : function(v) { return this.x * v.x + this.y * v.y + this.z * v.z; },
     // 类型转换
    convert:function(){ return new Color(this.x,this.y,this.z);},
    // 向量的叉乘
    cross : function(v) { return new Vector3(-this.z * v.y + this.y * v.z, this.z * v.x - this.x * v.z, -this.y * v.x + this.x * v.y); }
};

Vector3.zero = new Vector3(0, 0, 0);
