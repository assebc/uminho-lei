using System.ComponentModel.DataAnnotations;

namespace webOnlyFeiras.Model
{
    public class Feira
    {
        public enum TipoDeFeira
        {
            Corporativa,
            Mista,
            Informal
        }

        [Key]
        public int Id { get; set; }

        [Required]
        public string Nome { get; set; } = String.Empty;
        [Required]
        public string PathFotografia { get; set; } = String.Empty;
        [Required]
        public DateTime DataInicio { get; set; }
        [Required]
        public DateTime DataFim { get; set; }
        public string Descricao { get; set; } = String.Empty;
        [Required]
        public TipoDeFeira Tipo { get; set; }

        public List<Categoria> Categorias { get; set; }

    }
}
