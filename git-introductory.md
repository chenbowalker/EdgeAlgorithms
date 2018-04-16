#	Git 学习入门
##	git	3层结构
1. working directory工作区
2. staging index 暂存区
3. git directory(Repository)版本库

##	git中文件的4中状态：
1. untracked 未被追踪
2. Modified 表示工作区修改了某个文件但是还没有添加到暂存区
3. Staged 表示把工作区修改的文件添加到了暂存区但是没有提交到版本库
4. Committed 表示数据被安全的存储在本地库中

##	git的基本命令：

- git init 初始化git仓库，出现.git文件
- git add filename 将文件添加到暂存区
- git add .	将工作目录下所有修改的文件添加到暂存区
- git log 查看提交相关信息
- git status 查看项目状态
- git config --list 列出配置文件
- git config --global user.name cb
- git commit -m 'description' 将暂存区文件添加到版本库中
- git commit -am 'description' 跳过git add添加到暂存区命令，直接将工作区所有已跟踪的文件提交。

----------

###	git撤销操作如下：
- git checkout -filename 拉取暂存区的文件并将其替换工作区的文件
- git reset HEAD -filename 拉取最近一次提交的版本库中的这个文件到暂存区，该操作不影响工作区。
- git commit --amend 撤销上一次提交，并将暂存区的文件重新提交，可以选择修改description。

----------

### git删除操作如下：
- git rm filename 将工作去和暂存区的文件一并删除
- git rm --cached filename 将保存文件在工作区，删除在暂存区的文件。
- git rm -f filename 将工作和暂存区的文件一并删除
- git mv filename filename1 将工作区和暂存区的文件名一并修改
- git reset --option 版本号 （--hard代表将暂存区和工作区强行返回到版本号中的状态；--mixed代表将版本库和暂存区回退到版本号的状态，工作区不受影响；--soft将版本库回退到版本号的状态，工作区和暂存区不变）

----------

### Git分支
- git分支的创建、修改、切换和删除
- git branch 查看分支
- git branch branchname 创建分支
- git branch -m oldname newname 修改分支名称
- git checkout branchname 切换分支
- git branch -D branchname 删除分支

----------

###	分支的合并
- 分支的指针：HEAD指针永远指向当前工作的分支（指向当前分支的最新版本），在切换分支时指向新的分支。
- git diff 比较工作与暂存区文件的差异
- git diff --staged 比较暂存区与版本库的文件差异
- git diff 版本号 版本号 比较分支内两个版本的差异
- git diff 分支与分支 比较两个分支的最新提交版本差异
- git diff branchname 合并之前需要先切换到master分支，快速合并和冲突合并


----------

###	存储变更：
- git stash 将工作区的修改暂时存储在暂存区，然后工作区恢复到原来的状态。
- git stash list 查看当前stash列表
- git stash apply stash@{n} 恢复到最近一次的存储信息
- git stash drop stash@{num} 删除它


----------

###	git远程仓库

- git push 目的地址 分支名  （推送到远程仓库）
- git pull 目的地址 分支名  （拉取远程仓库）
- git remote add 地址名称 目的地址url  （将远程url重命名，以后地址名称就可以代替目的地址）


----------

###	创建.gitignore文件，忽略不想改变的内容。

- 删除暂存区的文件，并不改变工作区和版本库的文件。
- git rm filename --cached
- git commit -m 'description'


##	git help 命令名 
- eg: git help add