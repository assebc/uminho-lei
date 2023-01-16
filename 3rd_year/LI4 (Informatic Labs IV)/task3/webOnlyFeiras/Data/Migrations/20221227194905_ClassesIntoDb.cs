using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace webOnlyFeiras.Data.Migrations
{
    /// <inheritdoc />
    public partial class ClassesIntoDb : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Bancas",
                columns: table => new
                {
                    BancaId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    PathFotografia = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Descricao = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Bancas", x => x.BancaId);
                });

            migrationBuilder.CreateTable(
                name: "Encomenda",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    MoradaEnvio = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DataEnvio = table.Column<DateTime>(type: "datetime2", nullable: false),
                    DataEncomenda = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Estado = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Encomenda", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Feira",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nome = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    PathFotografia = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DataInicio = table.Column<DateTime>(type: "datetime2", nullable: false),
                    DataFim = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Descricao = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Tipo = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Feira", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Utilizador",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nome = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Email = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    DataNascimento = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Morada = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Contacto = table.Column<int>(type: "int", nullable: false),
                    Password = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    PathFotografiaPerfil = table.Column<int>(type: "int", nullable: false),
                    IsOrganizador = table.Column<bool>(type: "bit", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Utilizador", x => x.ID);
                });

            migrationBuilder.CreateTable(
                name: "CandidaturaParaBanca",
                columns: table => new
                {
                    IdCandidaturaBanca = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Data = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BancaId = table.Column<int>(type: "int", nullable: false),
                    PatrocinaFeira = table.Column<bool>(type: "bit", nullable: false),
                    Estado = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CandidaturaParaBanca", x => x.IdCandidaturaBanca);
                    table.ForeignKey(
                        name: "FK_CandidaturaParaBanca_Bancas_BancaId",
                        column: x => x.BancaId,
                        principalTable: "Bancas",
                        principalColumn: "BancaId",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Produto",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nome = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Descricao = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Preco = table.Column<decimal>(type: "decimal(18,2)", nullable: false),
                    Tipo = table.Column<int>(type: "int", nullable: false),
                    Stock = table.Column<int>(type: "int", nullable: false),
                    EncomendaId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Produto", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Produto_Encomenda_EncomendaId",
                        column: x => x.EncomendaId,
                        principalTable: "Encomenda",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "Categoria",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nome = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    FeiraId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Categoria", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Categoria_Feira_FeiraId",
                        column: x => x.FeiraId,
                        principalTable: "Feira",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "Carrinho",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    UtilizadorID = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Carrinho", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Carrinho_Utilizador_UtilizadorID",
                        column: x => x.UtilizadorID,
                        principalTable: "Utilizador",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "Marca",
                columns: table => new
                {
                    Nome = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    RepresentanteID = table.Column<int>(type: "int", nullable: false),
                    DataFundacao = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Nacionalidade = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Mercado = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    ImagePathLogotipo = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Morada = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    NIPC = table.Column<int>(type: "int", nullable: false),
                    Verificada = table.Column<bool>(type: "bit", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Marca", x => x.Nome);
                    table.ForeignKey(
                        name: "FK_Marca_Utilizador_RepresentanteID",
                        column: x => x.RepresentanteID,
                        principalTable: "Utilizador",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "CodigoPromocional",
                columns: table => new
                {
                    Codigo = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    PromocaoAplicada = table.Column<int>(type: "int", nullable: false),
                    CarrinhoId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CodigoPromocional", x => x.Codigo);
                    table.ForeignKey(
                        name: "FK_CodigoPromocional_Carrinho_CarrinhoId",
                        column: x => x.CarrinhoId,
                        principalTable: "Carrinho",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "Produtos",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    ProdutoId = table.Column<int>(type: "int", nullable: false),
                    AdicionadoEm = table.Column<DateTime>(type: "datetime2", nullable: false),
                    CarrinhoId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Produtos", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Produtos_Carrinho_CarrinhoId",
                        column: x => x.CarrinhoId,
                        principalTable: "Carrinho",
                        principalColumn: "Id");
                    table.ForeignKey(
                        name: "FK_Produtos_Produto_ProdutoId",
                        column: x => x.ProdutoId,
                        principalTable: "Produto",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "CandidaturaParaMarca",
                columns: table => new
                {
                    IdCandidaturaMarca = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    ResponsavelID = table.Column<int>(type: "int", nullable: false),
                    Data = table.Column<DateTime>(type: "datetime2", nullable: false),
                    MarcaNome = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    Estado = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_CandidaturaParaMarca", x => x.IdCandidaturaMarca);
                    table.ForeignKey(
                        name: "FK_CandidaturaParaMarca_Marca_MarcaNome",
                        column: x => x.MarcaNome,
                        principalTable: "Marca",
                        principalColumn: "Nome",
                        onDelete: ReferentialAction.NoAction);
                    table.ForeignKey(
                        name: "FK_CandidaturaParaMarca_Utilizador_ResponsavelID",
                        column: x => x.ResponsavelID,
                        principalTable: "Utilizador",
                        principalColumn: "ID",
                        onDelete: ReferentialAction.NoAction);
                });

            migrationBuilder.CreateIndex(
                name: "IX_CandidaturaParaBanca_BancaId",
                table: "CandidaturaParaBanca",
                column: "BancaId");

            migrationBuilder.CreateIndex(
                name: "IX_CandidaturaParaMarca_MarcaNome",
                table: "CandidaturaParaMarca",
                column: "MarcaNome");

            migrationBuilder.CreateIndex(
                name: "IX_CandidaturaParaMarca_ResponsavelID",
                table: "CandidaturaParaMarca",
                column: "ResponsavelID");

            migrationBuilder.CreateIndex(
                name: "IX_Carrinho_UtilizadorID",
                table: "Carrinho",
                column: "UtilizadorID");

            migrationBuilder.CreateIndex(
                name: "IX_Categoria_FeiraId",
                table: "Categoria",
                column: "FeiraId");

            migrationBuilder.CreateIndex(
                name: "IX_CodigoPromocional_CarrinhoId",
                table: "CodigoPromocional",
                column: "CarrinhoId");

            migrationBuilder.CreateIndex(
                name: "IX_Marca_RepresentanteID",
                table: "Marca",
                column: "RepresentanteID");

            migrationBuilder.CreateIndex(
                name: "IX_Produto_EncomendaId",
                table: "Produto",
                column: "EncomendaId");

            migrationBuilder.CreateIndex(
                name: "IX_Produtos_CarrinhoId",
                table: "Produtos",
                column: "CarrinhoId");

            migrationBuilder.CreateIndex(
                name: "IX_Produtos_ProdutoId",
                table: "Produtos",
                column: "ProdutoId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "CandidaturaParaBanca");

            migrationBuilder.DropTable(
                name: "CandidaturaParaMarca");

            migrationBuilder.DropTable(
                name: "Categoria");

            migrationBuilder.DropTable(
                name: "CodigoPromocional");

            migrationBuilder.DropTable(
                name: "Produtos");

            migrationBuilder.DropTable(
                name: "Bancas");

            migrationBuilder.DropTable(
                name: "Marca");

            migrationBuilder.DropTable(
                name: "Feira");

            migrationBuilder.DropTable(
                name: "Carrinho");

            migrationBuilder.DropTable(
                name: "Produto");

            migrationBuilder.DropTable(
                name: "Utilizador");

            migrationBuilder.DropTable(
                name: "Encomenda");
        }
    }
}
