using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Produto
    {
        public enum TipoDeProduto
        {
            Artigo,
            Serviço
        }
        [Key]
        public int Id { get; set; }
        [Required]
        public string Nome { get; set; } = String.Empty;
        public string Descricao { get; set; } = String.Empty;
        public Decimal Preco { get; set; }
        [Required]
        public TipoDeProduto Tipo { get; set; }
        public int Stock { get; set; }

    }
}
