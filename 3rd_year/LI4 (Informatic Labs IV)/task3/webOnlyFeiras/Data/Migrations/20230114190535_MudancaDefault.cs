using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace webOnlyFeiras.Data.Migrations
{
    /// <inheritdoc />
    public partial class MudancaDefault : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "IsOrganizador",
                table: "Utilizador");

            migrationBuilder.AddColumn<string>(
                name: "Role",
                table: "Utilizador",
                type: "nvarchar(max)",
                nullable: false,
                defaultValue: "");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Role",
                table: "Utilizador");

            migrationBuilder.AddColumn<bool>(
                name: "IsOrganizador",
                table: "Utilizador",
                type: "bit",
                nullable: false,
                defaultValue: false);
        }
    }
}
