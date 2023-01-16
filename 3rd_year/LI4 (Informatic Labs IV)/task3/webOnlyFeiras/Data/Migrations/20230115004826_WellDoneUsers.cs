using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace webOnlyFeiras.Data.Migrations
{
    /// <inheritdoc />
    public partial class WellDoneUsers : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CandidaturaParaMarca_Utilizador_ResponsavelID",
                table: "CandidaturaParaMarca");

            migrationBuilder.DropForeignKey(
                name: "FK_Carrinho_Utilizador_UtilizadorID",
                table: "Carrinho");

            migrationBuilder.DropForeignKey(
                name: "FK_Marca_Utilizador_RepresentanteID",
                table: "Marca");

            migrationBuilder.DropTable(
                name: "Utilizador");

            migrationBuilder.RenameColumn(
                name: "RepresentanteID",
                table: "Marca",
                newName: "RepresentanteId");

            migrationBuilder.RenameIndex(
                name: "IX_Marca_RepresentanteID",
                table: "Marca",
                newName: "IX_Marca_RepresentanteId");

            migrationBuilder.RenameColumn(
                name: "UtilizadorID",
                table: "Carrinho",
                newName: "UtilizadorId");

            migrationBuilder.RenameIndex(
                name: "IX_Carrinho_UtilizadorID",
                table: "Carrinho",
                newName: "IX_Carrinho_UtilizadorId");

            migrationBuilder.RenameColumn(
                name: "ResponsavelID",
                table: "CandidaturaParaMarca",
                newName: "ResponsavelId");

            migrationBuilder.RenameIndex(
                name: "IX_CandidaturaParaMarca_ResponsavelID",
                table: "CandidaturaParaMarca",
                newName: "IX_CandidaturaParaMarca_ResponsavelId");

            migrationBuilder.AlterColumn<string>(
                name: "RepresentanteId",
                table: "Marca",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(int),
                oldType: "int");

            migrationBuilder.AlterColumn<string>(
                name: "UtilizadorId",
                table: "Carrinho",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(int),
                oldType: "int");

            migrationBuilder.AlterColumn<string>(
                name: "ResponsavelId",
                table: "CandidaturaParaMarca",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(int),
                oldType: "int");

            migrationBuilder.AlterColumn<string>(
                name: "Name",
                table: "AspNetUserTokens",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(128)",
                oldMaxLength: 128);

            migrationBuilder.AlterColumn<string>(
                name: "LoginProvider",
                table: "AspNetUserTokens",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(128)",
                oldMaxLength: 128);

            migrationBuilder.AddColumn<int>(
                name: "Contacto",
                table: "AspNetUsers",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<DateTime>(
                name: "DataNascimento",
                table: "AspNetUsers",
                type: "datetime2",
                nullable: false,
                defaultValue: new DateTime(1, 1, 1, 0, 0, 0, 0, DateTimeKind.Unspecified));

            migrationBuilder.AddColumn<string>(
                name: "Morada",
                table: "AspNetUsers",
                type: "nvarchar(max)",
                nullable: false,
                defaultValue: "");

            migrationBuilder.AddColumn<string>(
                name: "Nome",
                table: "AspNetUsers",
                type: "nvarchar(max)",
                nullable: false,
                defaultValue: "");

            migrationBuilder.AddColumn<int>(
                name: "PathFotografiaPerfil",
                table: "AspNetUsers",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AlterColumn<string>(
                name: "ProviderKey",
                table: "AspNetUserLogins",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(128)",
                oldMaxLength: 128);

            migrationBuilder.AlterColumn<string>(
                name: "LoginProvider",
                table: "AspNetUserLogins",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(128)",
                oldMaxLength: 128);

            migrationBuilder.AddForeignKey(
                name: "FK_CandidaturaParaMarca_AspNetUsers_ResponsavelId",
                table: "CandidaturaParaMarca",
                column: "ResponsavelId",
                principalTable: "AspNetUsers",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Carrinho_AspNetUsers_UtilizadorId",
                table: "Carrinho",
                column: "UtilizadorId",
                principalTable: "AspNetUsers",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Marca_AspNetUsers_RepresentanteId",
                table: "Marca",
                column: "RepresentanteId",
                principalTable: "AspNetUsers",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_CandidaturaParaMarca_AspNetUsers_ResponsavelId",
                table: "CandidaturaParaMarca");

            migrationBuilder.DropForeignKey(
                name: "FK_Carrinho_AspNetUsers_UtilizadorId",
                table: "Carrinho");

            migrationBuilder.DropForeignKey(
                name: "FK_Marca_AspNetUsers_RepresentanteId",
                table: "Marca");

            migrationBuilder.DropColumn(
                name: "Contacto",
                table: "AspNetUsers");

            migrationBuilder.DropColumn(
                name: "DataNascimento",
                table: "AspNetUsers");

            migrationBuilder.DropColumn(
                name: "Morada",
                table: "AspNetUsers");

            migrationBuilder.DropColumn(
                name: "Nome",
                table: "AspNetUsers");

            migrationBuilder.DropColumn(
                name: "PathFotografiaPerfil",
                table: "AspNetUsers");

            migrationBuilder.RenameColumn(
                name: "RepresentanteId",
                table: "Marca",
                newName: "RepresentanteID");

            migrationBuilder.RenameIndex(
                name: "IX_Marca_RepresentanteId",
                table: "Marca",
                newName: "IX_Marca_RepresentanteID");

            migrationBuilder.RenameColumn(
                name: "UtilizadorId",
                table: "Carrinho",
                newName: "UtilizadorID");

            migrationBuilder.RenameIndex(
                name: "IX_Carrinho_UtilizadorId",
                table: "Carrinho",
                newName: "IX_Carrinho_UtilizadorID");

            migrationBuilder.RenameColumn(
                name: "ResponsavelId",
                table: "CandidaturaParaMarca",
                newName: "ResponsavelID");

            migrationBuilder.RenameIndex(
                name: "IX_CandidaturaParaMarca_ResponsavelId",
                table: "CandidaturaParaMarca",
                newName: "IX_CandidaturaParaMarca_ResponsavelID");

            migrationBuilder.AlterColumn<int>(
                name: "RepresentanteID",
                table: "Marca",
                type: "int",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<int>(
                name: "UtilizadorID",
                table: "Carrinho",
                type: "int",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<int>(
                name: "ResponsavelID",
                table: "CandidaturaParaMarca",
                type: "int",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<string>(
                name: "Name",
                table: "AspNetUserTokens",
                type: "nvarchar(128)",
                maxLength: 128,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<string>(
                name: "LoginProvider",
                table: "AspNetUserTokens",
                type: "nvarchar(128)",
                maxLength: 128,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<string>(
                name: "ProviderKey",
                table: "AspNetUserLogins",
                type: "nvarchar(128)",
                maxLength: 128,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.AlterColumn<string>(
                name: "LoginProvider",
                table: "AspNetUserLogins",
                type: "nvarchar(128)",
                maxLength: 128,
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");

            migrationBuilder.CreateTable(
                name: "Utilizador",
                columns: table => new
                {
                    ID = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Contacto = table.Column<int>(type: "int", nullable: false),
                    DataNascimento = table.Column<DateTime>(type: "datetime2", nullable: false),
                    Email = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Morada = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Nome = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Password = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    PathFotografiaPerfil = table.Column<int>(type: "int", nullable: false),
                    Role = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Utilizador", x => x.ID);
                });

            migrationBuilder.AddForeignKey(
                name: "FK_CandidaturaParaMarca_Utilizador_ResponsavelID",
                table: "CandidaturaParaMarca",
                column: "ResponsavelID",
                principalTable: "Utilizador",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Carrinho_Utilizador_UtilizadorID",
                table: "Carrinho",
                column: "UtilizadorID",
                principalTable: "Utilizador",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Marca_Utilizador_RepresentanteID",
                table: "Marca",
                column: "RepresentanteID",
                principalTable: "Utilizador",
                principalColumn: "ID",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
