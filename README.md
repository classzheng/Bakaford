# Bakaford: 琪露诺只是算术不好，符号计算能力可是最强的!!
这是一个个人的ATP (Automated Theorem Proving, 机器定理自动证明) 学习小项目, 主要收录自己学过的 ~~(大概吧)~~ 算法和⑨的一些梗图. 主体是toy style码风, 不过我喜欢过度包装一下下.  
需要注意的是, 大部分关于⑨的梗图图源网络, 如果觉得不合理请联系classzheng@outlook.com删除.  

<img width="644" height="741" alt="图源東方幻存神签 pdf截的图比较糊因为导出图片效果也好不到哪去" src="https://github.com/user-attachments/assets/33b8f958-dba0-4c5c-b206-10588ef67b9e" />

> Hint: 本作系《東方project》系列二次创作, 原作: ZUN  上海アリス幻楽団

# Bakaford官能团布局 (bushi)
- [x] CNF Resolver
- [x] 复系数质点法证明器 (这一版还是纯vibe coding，后面会改)
- [x] 基于模板元编程的HoTT系统 (重构版)
- [x] Incidence几何命题器
- [x] 基于Clifford Bracket面积法的证明器  
这里的Bakaford的ford就出自Clifford,没什么特殊意义. 基于Clifford括号的面积法将是Bakaford的主体.
- [x] 拉马努冰🧊模拟器
> - [ ] ~~国士无双max (FROZEN)~~ (这大概是一个通用的欧氏几何定理证明器罢 (心虚
- [ ] Bakaford<sub>4</sub> STEM  
尝试将高可读性证明器引入中学数学STEM教育体系.

# Bakaford入门
```shell
git clone https://github.com/classzheng/Bakaford.git
# Or clone it using GithubCLI
gh repo clone classzheng/Bakaford
```  
源文件在`~/bakaford`目录下. 每一个.cpp文件均可以单独编译, 我用的是  
```text
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/12/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Debian 12.2.0-14+deb12u1' --with-bugurl=file:///usr/share/doc/gcc-12/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-12 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/reproducible-path/gcc-12-12.2.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/reproducible-path/gcc-12-12.2.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 12.2.0 (Debian 12.2.0-14+deb12u1)
```  
直接在Shell Terminal中键入`g++ [filename].cpp`即可编译链接为可执行文件. 这里给出相对合适的观赏路径:  
1. **CNF Resolver** 对应单文件`cnfresolver.cpp`, 文档`一个基于归结原理的简单证明器.markdown`.
2. **TileQuizoner** 对应单文件`tilequizoneer.cpp`, 文档`用Incidence Tilings批量生产中学水平学生做不出来的钓鱼题.markdown`.
3. **基于Clifford Bracket面积法的证明器** 对应文件`bakaford.*pp`, 文档`用Clifford括号面积法斩碎你的incidence几何命题.markdown`.
4. 复系数质点法证明器 暂时未上传至仓库, 文档待编写.
5. **Ramanubin**, 对应文件`icy-ramanubin.*pp`, 文档`超越数系数对于Euclidean几何定理的通用化证明方法.markdown` (former).
6. ~~KokushimusoMAX~~ (FROZEN), 未上传至仓库, 文档`超越数系数对于Euclidean几何定理的通用化证明方法.markdown` (former).
7. **D.E.S.**; Geometric D.E.S., 对应`des.*pp`,`geometricdes.cpp`, 文档`幻想乡最强几何定理证明助手.markdown`.
8. Bakaford<sub>4</sub> STEM, 暂时未上传至仓库, 位于`~/education`, 文档`幻想乡最强几何定理证明助手.markdown`.
9. **TemplateUniverse**, 前身为HoTT System Abstract. 前者对应文件`templateuniverse.*pp`, 后者对应文件`hottreasoner.deprecated.*pp`,`socrates.notavailable.cpp`
Markdown格式文档均存放在`~/documents`目录下, 建议使用[Typora](https://typora.io/)阅读.

---

~~话说为了能充分体现咱的toy-style魅力时刻~~, 用户在用g++编译时不得不删掉自 21Nov.2026(DDMMYY) 起加入的Fumo注释, 或者用clang编译了. (大悲)
```cpp
#if false
//                            ??/
"⠀⠀⣠⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀    ??/
⠀⠀⡜⠁⠀⠈⢢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠋⠷⠶⠱⡄    ??/
⠀⢸⣸⣿⠀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠫⢀⣖⡃⢀⣸⢹    ??/
⠀⡇⣿⣿⣶⣤⡀⠀⠀⠙⢆⠀⠀⠀⠀⠀⣠⡪⢀⣤⣾⣿⣿⣿⣿⣸    ??/
⠀⡇⠛⠛⠛⢿⣿⣷⣦⣀⠀⣳⣄⠀⢠⣾⠇⣠⣾⣿⣿⣿⣿⣿⣿⣽    ??/
⠀⠯⣠⣠⣤⣤⣤⣭⣭⡽⠿⠾⠞⠛⠷⠧⣾⣿⣿⣯⣿⡛⣽⣿⡿⡼    ??/
⠀⡇⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⣿⣿⣮⡛⢿⠃    ??/
⠀⣧⣛⣭⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣷⣎⡇    ??/
⠀⡸⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣷⣟⡇    ??/
⣜⣿⣿⡧⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⣄⠀⠀⠀⠀⠀⣸⣿⡜⡄    ??/
⠉⠉⢹⡇⠀⠀⠀⢀⣞⠡⠀⠀⠀⠀⠀⠀⡝⣦⠀⠀⠀⠀⢿⣿⣿⣹    ??/
⠀⠀⢸⠁⠀⠀⢠⣏⣨⣉⡃⠀⠀⠀⢀⣜⡉⢉⣇⠀⠀⠀⢹⡄⠀⠀    ??/
⠀⠀⡾⠄⠀⠀⢸⣾⢏⡍⡏⠑⠆⠀⢿⣻⣿⣿⣿⠀⠀⢰⠈⡇⠀⠀    ??/
⠀⢰⢇⢀⣆⠀⢸⠙⠾⠽⠃⠀⠀⠀⠘⠿⡿⠟⢹⠀⢀⡎⠀⡇⠀⠀    ??/
⠀⠘⢺⣻⡺⣦⣫⡀⠀⠀⠀⣄⣀⣀⠀⠀⠀⠀⢜⣠⣾⡙⣆⡇⠀⠀    ??/
⠀⠀⠀⠙⢿⡿⡝⠿⢧⡢⣠⣤⣍⣀⣤⡄⢀⣞⣿⡿⣻⣿⠞⠀⠀⠀    ??/
⠀⠀⠀⢠⠏⠄⠐⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠳⢤⣉⢳⠀⠀⠀    ??/
⢀⡠⠖⠉⠀⠀⣠⠇⣿⡿⣿⡿⢹⣿⣿⣿⣿⣧⣠⡀⠀⠈⠉⢢⡀⠀    ??/
⢿⠀⠀⣠⠴⣋⡤⠚⠛⠛⠛⠛⠛⠛⠛⠛⠙⠛⠛⢿⣦⣄⠀⢈⡇⠀    ??/
⠈⢓⣤⣵⣾⠁⣀⣀⠤⣤⣀⠀⠀⠀⠀⢀⡤⠶⠤⢌⡹⠿⠷⠻⢤⡀    ??/
⢰⠋⠈⠉⠘⠋⠁⠀⠀⠈⠙⠳⢄⣀⡴⠉⠀⠀⠀⠀⠙⠂⠀⠀⢀⡇    ??/
⢸⡠⡀⠀⠒⠂⠐⠢⠀⣀⠀⠀⠀⠀⠀⢀⠤⠚⠀⠀⢸⣔⢄⠀⢾⠀    ??/
⠀⠑⠸⢿⠀⠀⠀⠀⢈⡗⠭⣖⡒⠒⢊⣱⠀⠀⠀⠀⢨⠟⠂⠚⠋⠀    ??/
⠀⠀⠀⠘⠦⣄⣀⣠⠞⠀⠀⠀⠈⠉⠉⠀⠳⠤⠤⡤⠞⠀       "??/
      FUMOFUMOFUMO            ??/
i would like to say that i was on purpose.
#endif
```

**Baka!** <img width="64" height="64" src="https://github.com/classzheng/Bakaford/blob/main/image/_cgi-bin_mmwebwx-bin_webwxgetmsgimg__&MsgID=4831845180502399271&skey=@crypt_6577b684_63b62ba79f6a410a9a1862355baa09a6&mmweb_appid=wx_webfilehelper.jpg?raw=true" /> 这里我使用的clang编译器环境信息是:  
```text
Debian clang version 14.0.6
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12
Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/12
Candidate multilib: .;@m64
Selected multilib: .;@m64
```
不过我发现部分代码不能被clang编译, 不知道为啥, 可能是GNU C/C++写惯了罢. (捂脸)
