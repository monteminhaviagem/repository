<?php
namespace module\admin\guide\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_guide."/controller/Guide.inc");

use module\admin\Admin;
use module\admin\guide\controller\Guide;

class Git extends Admin {
	
	const ID = 'd7e18d481062ab445423b35b734c0e50';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_content() {
		global $path_url_img_guide;
		
		$controller = new Guide();
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Git</h1>
						</div>
					</div>
					
					<!-- BEGIN TAB -->
					<div class="panel-body">
						<ul class="nav nav-tabs">
							<li class="active"><a href="#resume" data-toggle="tab"><i class="fa fa-info"></i> Resumo</a></li>
							<li><a href="#repository" data-toggle="tab"><i class="fa fa-database"></i> Repositórios Remotos</a></li>
							<li><a href="#process" data-toggle="tab"><i class="fa fa-gears"></i> Processos</a></li>
							<li><a href="#basic" data-toggle="tab"><i class="fa fa-file-text-o"></i> Comandos Básicos</a></li>
							<li><a href="#extra" data-toggle="tab"><i class="fa fa-file-text-o"></i> Comandos Extras</a></li>
						</ul>
						
						<div class="tab-content" style="padding-top: 20px;">
							<div class="tab-pane fade in active" id="resume">
								<p>Git faz com que seus arquivos sempre estejam em um dos três estados fundamentais:<br><br>
								consolidado (committed)<br>
								modificado (modified)<br>
								preparado (staged)<br><br>
								Dados são ditos consolidados quando estão seguramente armazenados em sua base de dados local.<br>
								Modificado trata de um arquivo que sofreu mudanças mas que ainda não foi consolidado na base de dados.<br>
								Um arquivo é tido como preparado quando você marca um arquivo modificado em sua versão corrente para que ele faça parte do snapshot do próximo commit (consolidação).</p>
								
								<p>Os três estados de um repositório são "Working Directory", que são os arquivos que temos em nosso repositório e podemos modificá-los "Index" ou "Staging Area", que é uma visão preliminar das modificações em nossos arquivos que queremos definir como um novo passo do projeto "HEAD", que é um passo completo de nosso trabalho, usado como referência para a comparação com nosso "Working Directory".</p>
								
								<img src="{$path_url_img_guide}/git-operations.png">
							</div>
							
							<div class="tab-pane fade" id="repository">
								<pre>------------
-- GITHUB --
------------
repository: https://github.com/monteminhaviagem/repository.git
username:   mmv@monteminhaviagem.com.br
password:   mmv@2016

-------------
-- HOMOLOG --
-------------
repository: ssh://104.236.11.153/home/mmv/repository
username:   mmv
password:   ?hos01@mmv!

--------------
-- PRODUÇÃO --
--------------
repository: ssh://104.236.86.174/home/mmv/repository
username:   mmv
password:   ?pos01@mmv!</pre>
							</div>
							
							<div class="tab-pane fade" id="process">
								<div class="header">
									<a href="http://storage.monteminhaviagem.com.br/empresas/abadar/processos/bizagi/git.bpm" target="_blank">
										<small class="text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<img src="{$path_url_img_guide}/git-local.png"><br><br>
								<img src="{$path_url_img_guide}/git-remote.png"><br><br>
								<img src="{$path_url_img_guide}/git-developer.png"><br><br>
								<img src="{$path_url_img_guide}/git-homolog.png"><br><br>
								<img src="{$path_url_img_guide}/git-production.png">
							</div>
							
							<div class="tab-pane" id="basic">
								<pre>----------------------------
-- INICIAR UM REPOSITÓRIO --
----------------------------
git init

-------------------------------------------------
-- LISTAR ARQUIVOS QUE ESTÃO SENDO MONITORADOS --
-------------------------------------------------
git ls-files

---------------------------------------------------------------------
-- ADICIONAR ARQUIVOS NA STAGING AREA (PARA QUE SEJAM MONITORADOS) --
---------------------------------------------------------------------
git add nome_do_arquivo (adiciona um arquivo específico)

-------------------------------------
-- EXIBIR STATUS DE UM REPOSITÓRIO --
-------------------------------------
git status (exibe um resumo de quais arquivos foram modificados, adicionados ou excluídos de seu Working Directory, em comparação com o HEAD)

------------------------------
-- ALTERAR DADOS DE USUÁRIO --
------------------------------
-- ALTERAR APENAS PARA O REPOSITÓRIO ATUAL
git config user.name "your name"
git config user.email "your email"
OBS.: As configurações na pasta específica do projeto [.git/config], sobrepoe as demais

-- ALTERAR PARA TODOS OS REPOSITÓRIOS
git config --global user.name "your name"
git config --global user.email "your email"
OBS.: Os comandos acima, adicionam as configurações no arquivo de usuário ~/.gitconfig

-- ALTERAR PARA TODOS OS USUÁRIOS
git config --system user.name "your name"
git config --system user.email "your email"
OBS.: Os comandos acima, adicionam as configurações no arquivo /usr/local/etc/gitconfig

-------------------
-- CONFIGURAÇÕES --
-------------------
git config --list (para listar todas as configurações que o Git encontrar naquele momento)
git config user.name (lista valores para a configuração usar.name)

-------------------------------------
-- EFETIVAR AS ALTERAÇÕES (COMMIT) --
-------------------------------------
git commit -m "description"

-----------------------------------------------
-- EXIBIR TODOS OS COMMITS DE UM REPOSITÓRIO --
-----------------------------------------------
git log
git log -p (exibir maiores detalhes sobre o que foi alterado dentro de cada arquivo)

--------------------------
-- REPOSITÓRIOS REMOTOS --
--------------------------
git remote (exibe quais repositórios remotos estãs configurados)
git remote add repository_name repository_url (adiciona um repositório remoto)
git push repository_name branch_name (envia a branch especificada para o repositório remoto)
git pull repository_name branch_name (recebe a branch especificada do repositório remoto)
git push -u repository_name branch_name (o parametro -u liga a branch local com a respectiva branch remota)
git clone repository_url [nome_pasta_local] (adiciona um repositorio remoto na maquina local e já faz o pull dos arquivos)

-------------
-- BRANCHS --
-------------
git branch (exibe todas as branchs locais)
git branch -r (exibe todas as branchs remotas)
git branch -a (exibe todas as branchs locais e remotas)
git branch nome_da_branch (criar uma nova branch)
git branch -t nome_da_branch origin/design (cria a branch local associando com a branch remota)
git checkout nome_da_branch (altera para a nova branch)
git checkout -b design (cria uma nova branch chamada design e ja faz o checkout pra ela)
git checkout -t origin/design (uma nova branch local chamada design é criada, muda-se para essa branch, copiamos todo o conteúdo da branch remota design do repositório referente ao origin e trackeamos as duas branches)
git branch -d design (a branch local design será deletada)
git push origin :design (deleta a branch remota design)

----------
-- TAGS --
----------
git tag (exibe todas as tags locais)
git show tag_name (exibe dados da tag)
git checkout tag_name (altera para a nova tag)

git tag -a v1.2 9fceb02 (Criar tag baseada no commit 9fceb02)
git push production v1.5 (Por padrão, o comando git push não transfere tags para os servidores remotos)
git push production --tags (Ele irá transferir todas as suas tags que ainda não estão no servidor remoto)
</pre>
							</div>
							
							<div class="tab-pane" id="extra">
								<pre>---------------------------------------------------------------------
-- ADICIONAR ARQUIVOS NA STAGING AREA (PARA QUE SEJAM MONITORADOS) --
---------------------------------------------------------------------
git add *.html (adiciona todos os arquivos com a extensão html)
git add . (adiciona todos os arquivos do diretório corrente)
git add nome_da_pasta/ (adiciona todos os arquivos de uma determinada pasta)
git add --all (adiciona todas as pastas, subpastas e arquivos do repositório)
git add -i (habilita o modo interativo, onde você vai selecionando qual arquivo deverá ser adicionar a staging area)

-----------------------------------------
-- EXIBIR MAIORES DETALHES DOS COMMITS --
-----------------------------------------
git whatchanged
git whatchanged -p (exibir maiores detalhes sobre o que foi alterado dentro de cada arquivo)

git blame css/global.css (exibe os detalhes de alteração do arquivo)

----------------
-- COMPARAÇÃO --
----------------
git diff v01 v02 (exibe as diferenças entre as duas versões)

-----------------------------------------
-- VISUALIZANDO O HISTÓRICO DE COMMITS --
-----------------------------------------
git log
git log --pretty=oneline
git log --pretty=format:"%h - %an, %ar : %s"
git log --pretty=format:"%h %s" --graph
git log -p
git log -p -2 ("mostra apenas os dois últimos commits")
git log --stat
git log --since=2.weeks ("pega a lista de commits feitos nas últimas duas semanas")
git log --pretty="%h - %s" --author=gitster --since="2008-10-01" --before="2008-11-01" --no-merges -- t/
("ver quais commits modificaram arquivos de teste no histórico do código fonte do Git que foram commitados por Julio Hamano em Outubro de 2008, e não foram merges")

-- Opções
-p	- Mostra o patch introduzido com cada commit.
--stat -	Mostra estatísticas de arquivos modificados em cada commit.
--shortstat -	Mostra somente as linhas modificadas/inseridas/excluídas do comando --stat.
--name-only	- Mostra a lista de arquivos modificados depois das informações do commit.
--name-status	- Mostra a lista de arquivos afetados com informações sobre adição/modificação/exclusão dos mesmos.
--abbrev-commit	- Mostra somente os primeiros caracteres do checksum SHA-1 em vez de todos os 40.
--relative-date	- Mostra a data em um formato relativo (por exemplo, “2 semanas atrás”) em vez de usar o formato de data completo.
--graph	- Mostra um gráfico ASCII do branch e histórico de merges ao lado da saída de log.
--pretty	- Mostra os commits em um formato alternativo. Opções incluem oneline, short, full, fuller, e format (onde você especifica seu próprio formato).

-(n)	- Mostra somente os últimos n commits.
--since, --after	- Limita aos commits feitos depois da data especificada.
--until, --before	- Limita aos commits feitos antes da data especificada.
--author	- Somente mostra commits que o autor casa com a string especificada.
--committer	- Somente mostra os commits em que a entrada do commiter bate com a string especificada.

-- Tabela de opção para format
%H	- Hash do commit
%h	- Hash do commit abreviado
%T	- Árvore hash
%t	- Árvore hash abreviada
%P	- Hashes pais
%p	- Hashes pais abreviados
%an	- Nome do autor
%ae	- Email do autor
%ad	- Data do autor (formato respeita a opção -date=)
%ar	- Data do autor, relativa
%cn	- Nome do committer
%ce	- Email do committer
%cd	- Data do committer
%cr	- Data do committer, relativa
%s	- Assunto

------------------------
-- REMOVENDO ARQUIVOS --
------------------------
git rm grit.gemspec
Se você modificou o arquivo e já o adicionou na área de seleção, você deve forçar a remoção com a opção -f

git rm --cached readme.txt
Manter o arquivo no seu disco rígido mas não quer que o Git o monitore mais

------------------------
-- IGNORANDO ARQUIVOS --
------------------------
Exemplo de um arquivo .gitignore
# um comentário - isto é ignorado
# sem arquivos terminados em .a
*.a
# mas rastreie lib.a, mesmo que você tenha ignorado arquivos terminados em .a acima
!lib.a
# apenas ignore o arquivo TODO na raiz, não o subdiretório TODO
/TODO
# ignore todos os arquivos no diretório build/
build/
# ignore doc/notes.txt mas, não ignore doc/server/arch.txt
doc/*.txt

As regras para os padrões que você pode pôr no arquivo .gitignore são as seguintes:

Linhas em branco ou iniciando com # são ignoradas.
Padrões glob comuns funcionam (expressões regulares simples que os shells usam).
Você pode terminar os padrões com uma barra (/) para especificar diretórios.
Você pode negar um padrão ao iniciá-lo com um ponto de exclamação (!).

Um asterísco (*) significa zero ou mais caracteres;
[abc] condiz com qualquer um dos caracteres de dentro dos colchetes (nesse caso, a, b, ou c);
um ponto de interrogação (?) condiz com um único caractere;
e os caracteres separados por hífen dentro de colchetes ([0-9]) condizem à qualquer um dos caracteres entre eles (neste caso, de 0 à 9).

------------------------
-- PSEUDÔNIMOS NO GIT --
------------------------
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
</pre>
							</div>
						</div>
					</div>
					<!-- END TAB -->
				
					
				<div class="row">
						<div class="col-lg-12">
							
						</div>
					</div>
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Git";
	}
}

?>