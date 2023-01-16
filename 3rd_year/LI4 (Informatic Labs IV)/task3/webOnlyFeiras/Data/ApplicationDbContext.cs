using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using webOnlyFeiras.Model;

namespace webOnlyFeiras.Data
{
    public class ApplicationDbContext : IdentityDbContext<Utilizador>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<Banca> Bancas { get; set; }
        public DbSet<CandidaturaParaBanca> CandidaturaParaBanca { get; set; }
        public DbSet<CandidaturaParaMarca> CandidaturaParaMarca { get; set; }
        public DbSet<Carrinho> Carrinho { get; set; }
        public DbSet<Categoria> Categoria { get; set; }
        public DbSet<CodigoPromocional> CodigoPromocional { get; set; }
        public DbSet<Encomenda> Encomenda { get; set; }
        public DbSet<Feira> Feira { get; set; }
        public DbSet<Marca> Marca { get; set; }
        public DbSet<Produto> Produto { get; set; }
        public DbSet<Produtos> Produtos { get; set; }


    }
}