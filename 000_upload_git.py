from subprocess import Popen, PIPE, call
from git.repo import Repo
import re, os

def RunPopen(cmd :str):
    p = Popen(cmd, shell=True, stdout=PIPE)
    return p.stdout.read().decode()

def RunCommand(cmd :str):
    call(cmd, shell=True)

def deleteListData(OriginalList :list, dataContent: str, x = 0):
    while x < len(OriginalList):
        if OriginalList[x][:3] == dataContent:
            OriginalList.pop(x);
            x -= 1
        x += 1

class git_process:
    def __init__(self, folder_path :str = '.'):
        self.repo = Repo.init(folder_path)
        self.remote_url = 'git@github.com:sngrotesque/cryptographic_algorithm.git'
        self.commit  = 'cryptographic'
        self.version = 'v1.0.1'
        self.folderPath = folder_path

        self.path = os.listdir(folder_path)
        try: self.path.remove('.git')
        except ValueError: pass

    def view(self):
        print(f'>>>> +---------- 现有文件(BEGIN) ----------+')
        for fileName in self.path:
            print(f'>>>> + {fileName:<35} +')
        print(f'>>>> +---------- 现有文件(END)   ----------+')

    def versionCheck(self):
        versionList = re.findall(r'\w+\_v[\d.]+|v[\d.]+', RunPopen('git branch'), re.S)
        if self.version not in versionList:
            RunCommand(f'git checkout -b {self.version}')
        if self.version in versionList:
            RunCommand(f'git checkout {self.version}')

    def init(self):
        if not os.path.exists(f'{self.folderPath}/.git'):
            self.repo.create_remote(name='origin', url=self.remote_url)

    def push(self):
        for file_name in self.path:
            self.repo.index.add(items = file_name)
        self.repo.index.commit(self.commit)
        self.repo.remote().push(self.version)

git = git_process()
git.init()
git.versionCheck()
git.view()
git.push()


