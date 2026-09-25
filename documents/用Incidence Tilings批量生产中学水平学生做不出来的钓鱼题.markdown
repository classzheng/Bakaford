# 用Incidence Tilings批量生产中学水平学生做不出来的钓鱼题

不是我写的：

![用李代数批量生产正常人做不出来的高代题824 赞同 · 33 评论 文章](https://pica.zhimg.com/v2-393ef099308a9140dd5e33c5e66fda7a.jpg?source=7e7ef6e2&needBackground=1)

参考了论文：

原论文大概看到了p24，但是因为英语功底不行所以只能算是一知半解OwQ  主要是看了这一篇 [射影几何和「拼图」一样简单？！ - 知乎](https://zhuanlan.zhihu.com/p/2037091015455158802) 之后的一个灵感，属于Master Theorem的简单逆用，做出来的一个有点意思的toy。

这里我会简单总结一下 [射影几何和「拼图」一样简单？！ - 知乎](https://zhuanlan.zhihu.com/p/2037091015455158802) 的【基础】部分内容，至于论文看没看完，只能是 “阶段性正确的错误”的问题了，目前来看是足够的。如果有问题，恳请予以纠正。

![Figure 1:  // 这里的&quot;^&quot;应该是\cap，直线与点的关系不重要](https://pic1.zhimg.com/80/v2-e13b07ede0fad37c3a7154a340dced44_720w.png?source=ccfced1a)

## [射影几何和「拼图」一样简单？！ - 知乎](https://zhuanlan.zhihu.com/p/2037091015455158802) 【基础】部分概况&总结

![Figure 2: Definition of a coherent tile.](https://pic1.zhimg.com/80/v2-79364ae2361febf51e697d7a99de1392_720w.png?source=ccfced1a)

对于上图中的情形，即 在二维射影平面上的直线l与直线m有交点 \[\ell\cap m\] 与点A和点B 共线，被称为conherent的，也就是incidence condition (*) 。这里引用一下原文

> **Remark 2.2.** In the case of the projective plane ( \[\text{dim }\mathbb{P}=2\] ), a coherent tile involves two points A,B and two lines ℓ,m not incident to them such that either A = B or \[\ell =m\] or else the line (AB) passes through the point \[\ell\cap m\]. See Figure 2

![Figure 3: 这是一块最简单的tile](https://pic1.zhimg.com/80/v2-14aad03db0d5135e1e89810f3b886e33_720w.png?source=ccfced1a)

我们可以将所有的incidence condition都抽象成上图的一块tile，[射影几何和「拼图」一样简单？！ - 知乎](https://zhuanlan.zhihu.com/p/2037091015455158802) 中被翻译为“拼图”。这样的翻译倒是挺贴切的，也是简单易懂的，但这里选择保留原文，因为有些机翻过来似乎很奇怪，所以为了避免歧义，其次尽量采用 [射影几何和「拼图」一样简单？！](https://zhuanlan.zhihu.com/p/2037091015455158802) 中的翻译。

我们可以把不同的tile拼在一起，例如

![Figure 4:  Split a 2×2k square into 4k unit squares and glue its opposite sidesto each other to get a tiling of the torus by 4k tiles...](https://picx.zhimg.com/80/v2-920fc83701f9207f659249afe680dffd_720w.png?source=ccfced1a)

同时，不证自明地，一块tile也能对应一个incidence condition，也就是Figure 3能对应Figure 2的情形。由此，我们自然也有主定理（Master Theorem）：

> If condition (∗) holds for all tiles but one, then it also holds for the remaining tile.

也就是说，如果一张图中除了 \[t_0\] 外所有的tiles都coherent的话，那么 \[t_0\] 也是coherent的。这个并不难理解，毕竟我们在构造图的时候，自然会构造出额外的tiles，而这些tiles本就应该是coherent的。举个例子，见Figure 1，如果我们是依次构造 \[\{v_1,l_2,v_3,l_4\},   \{v_1,l_0,v_5,l_4\},   \{v_3,l_4,v_5,l_2\}\] 的话，我们会发现刚好形成了 \[t_0:=\{v_1,l_0,v_5,l_2\}\] ，而 \[t_0\] 也要对应一个incidence condition，因此是conherent的。

上面这番论述并不严谨，不过是点到为止，感兴趣的可以去看看原文

## Incidence Tilings要怎么用来恶心人的？

我们刚才认为一块tile能对应一个incidence condition，所以如果我们能用随机数构造一张含有tiles的图，对应回它的几何意义不就行了嘛。

![我真是个 天 (バ) 才 (カ)](https://pic1.zhimg.com/80/v2-a8398770fd345467e6d3a9532b25c7f8_720w.jpg?source=ccfced1a)

当然，由主定理，这些tiles是知(n-1)推1的。我目前没写完自然语言命题的部分（现已写完一个比较简单的格式化输出），需要人工整理一下。需要注意的是，须让最后图中含有的tiling数量大于构造的数量，这样构造出来的题目才是有意义的，而多出来的tile(s)就是结论，不过这不重要，主定理确保它们是是知(n-1)推1的。并且，最后生成的#tile必须大于或等于3，不难发现otherwise是无意义的。

```
        for(int epc=0; g.findtilings()<=std::max(epc,3) && epc<=rho*volume; epc++) {
		int v0idx=0, v1idx=0, l0idx=0, l1idx=0;
		while(v0idx==v1idx||l0idx==l1idx) {
			v0idx = rand()%(volume/2);
			v1idx = rand()%(volume/2);
			l0idx = rand()%(volume/2)+1;
			l1idx = rand()%(volume/2)+1;
			bool taut0=(g.lineref[l0idx].first==v0idx&&g.lineref[l0idx].second==v1idx)||(g.lineref[l0idx].first==v1idx&&g.lineref[l0idx].second==v0idx);
			bool taut1=(g.lineref[l1idx].first==v0idx&&g.lineref[l1idx].second==v1idx)||(g.lineref[l1idx].first==v1idx&&g.lineref[l1idx].second==v0idx);
			if(!taut0&&!taut1) continue;
		}
		g.addtiling(v0idx,l0idx,v1idx,l1idx);
	}
```

注意看循环条件。

完整代码可以看看我在*gayhub*上的仓库Bakaford，到时候会收录一些机器定理自动证明的toys。不过，代码写的并不十分好看，反而有很多冗余。还有就是，有时候生成的定理很奇怪，Figure 1就是一个废话定理，但生成太长了又不大好钓鱼，笑一笑罢了。

看来某人得加下班了呢。

## 2026.6.6 补录

坏了我好像忘记给直线分配符号表了 (＃°Д°) 改完后已经上传Github，顺便把搞笑参数整理了一下，删掉无作用的shrink函数（构造过程中不可能出现shrink函数能删除的多余边）

项目的主体码风是toy style加上一点过度包装，不建议学习，但是可以clone下来玩一玩。

封面图源网络，我给加上了!?Tautolo⑨y?!的字样。

## 2026.6.6 补录

符号表分配疑似有点问题，这回真改好了，但没写等效直线的剪枝，我自己看着办吧。

上面这张截图的符号表是错的。

## 2026.7.26 补录

![环境是Debian Linux × WSL2，使用C++编写](https://picx.zhimg.com/80/v2-147eba609ed0b5391ea44079fe330406_720w.png?source=ccfced1a)

*byd符号表查重就7行代码，能绷住两个月不写我也大抵是个神人*

```
	auto exist=[&](int s0, int s1)->bool {
		for(auto& is: g.lineref) {
			if(is.first==s0&&is.second==s1) return true;
			if(is.first==s1&&is.second==s0) return true;
		}
		return false;
	};
```

这里就先告一段落，后面我会根据 [这篇论文](https://doi.org/10.1360/za2007-37-5-523) 写一个简单的Clifford括号面积法证明器来解决此类*猎奇* incidence几何定理。btw， [Incidences and tilings](https://arxiv.org/abs/2305.07728) 这篇论文我前面  现（早）在（就）看的差不多，因为没什么需要，加上忙，所以p24以后基本没继续看下去了。

[Automated Theorem Proving in Projective Geometry](https://doi.org/10.1360/za2007-37-5-523)

![Desargues定理，一个很经典的incidence几何命题](https://picx.zhimg.com/80/v2-06123aac1175c026eb7763f107b2c8a3_720w.jpg?source=ccfced1a)

![Automated Theorem Proving in Projective Geometry中证明器给出的简短可读证明](https://picx.zhimg.com/80/v2-1392fd280d97d9e070f57486d69b7489_720w.jpg?source=ccfced1a)

这里的 \[\overset{\text{remove factors}}\simeq\] 符号意思是去掉下划线的公因子。其实不去掉也没有问题，这里是为了简化计算和方便人工检验。这里的中括号 \[\left[\cdot,\cdot,\cdot\right]\] 是Clifford括号，一个三元函数，表示三点围成三角形的有向面积（的两倍？）。我暂时没找到国内相关的介绍，不过这样的写法在AoPS中挺常见的。

在 《仿射括号代数理论与算法及其在几何定理机器证明中的应用》张宁等 中，有时也会看到二元的Clifford括号，这里引入了边界算子σ，正在尝试读懂中。

![原问题是：任做一条直线分别交双曲线及其渐近线于1，7，9，8，则6点平分89 当且仅当6点平分17](https://pic1.zhimg.com/80/v2-ff02d19f3fd88f13cffd624244467010_720w.png?source=ccfced1a)

## 2026.9.19 补录

改了格式，搬运到我的个人blogger上

[@classzheng — Blog](classzheng.github.io/)