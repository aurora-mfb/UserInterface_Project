# UTAD-UI-FPS-Public

<h1 align="center"> Práctica sobre interfaces: Creación de un arbol de habilidades. </h1>

<p align="center">
  <b>Universidad U-Tad· Asignatura: Interfaces</b><br>
  <i>Implementación de un sistema de árbol de habilidades con dependencias y desbloqueo progresivo.</i>
</p>

El propósito de esta actividad ha sido implementar un sistema de árbol de habilidades (Skill Tree) en Unreal Engine, donde cada habilidad (Skill) puede estar condicionada por otras previas y requiere la interacción del jugador para desbloquearse consumiendo puntos.

Su implementación se realizó de la siguiente manera:

<h2 align="center"> 1. USkillWidget Class </h2>
Esta clase representa una habilidad individual dentro del árbol. Sus principales funciones son:

<h3> NativeConstruct (Inicialización) </h3>
<ul>
  <li>Se obtiene referencia al personaje (AUTAD_UI_FPSCharacter) para acceder a los puntos de habilidad disponibles.</li>
  <li>Se configura el estilo visual del botón (FButtonStyle) para mostrar el icono correspondiente a la habilidad bloqueada o desbloqueada.</li>
  <li>Se configura lo que ocurre si se pulsa el botón:
    <ul>
      <li>OnButtonPressed: Se valida si el jugador tiene puntos suficientes, si la habilidad ya está desbloqueada y si las habilidades previas requeridas lo están. En caso negativo, se muestra un mensaje de notificación.</li>
      <li>OnButtonReleased: Cancela la acción si el jugador no mantiene la pulsación el tiempo suficiente.</li>
    </ul>
  </li>
  <li>Se inicializa la barra de confirmación (ProgressBar_Confirm) en estado oculto.</li>
  <li>Se setean los puntos que tiene el jugador en el momento.</li>
</ul>

<h3> NativeTick: </h3>
<ul>
  <li>Gestiona el tiempo de pulsación (hold). Al completarse el tiempo requerido, se confirma el desbloqueo.</li>
</ul>

<h3> OnButtonClicked: </h3>
<ul>
  <li>Marca la habilidad como desbloqueada y activa los cambios visuales y lógicos correspondientes.</li>
</ul>

<h3> UnlockSkill: </h3>
<ul>
  <li>Se descuentan los puntos del jugador.</li>
 <li>Se cambia el estilo del botón para reflejar el nuevo estado (icono desbloqueado en todos los estados visuales).</li>
</ul>

<h3> ShowNotification: </h3>
<ul>
  <li>Muestra un widget de aviso (UNotificationWidget) con mensajes contextuales como "No hay puntos suficientes" o "Debe seleccionar una habilidad anterior".</li>
</ul>

<h2 align="center"> 2. USkillTreeWidget </h2>
Esta clase representa el contenedor de todo el árbol de habilidades. Sus funciones principales son:

<h3> NativeConstruct: </h3>
<ul>
 <li>Se recorre el CanvasPanel para recoger todas las instancias de USkillWidget.</li>
 <li>Se genera un mapa (SkillMap) que relaciona el SkillID con su widget correspondiente.</li>
 <li>Se rellenan las referencias de dependencias (m_pPreviousSkills) en cada widget, en función de los identificadores declarados en el editor (m_PreviousSkillIDs).</li>
</ul>

<h3> NativeOnMouseButtonDown (Entrada de usuario): </h3>
<ul>
  <li>Devuelve un FReply::Handled para evitar interacciones no deseadas en el lienzo.</li>
</ul>

<h2 align="center"> Decisiones de diseño </h2>
<ul>
 <li>Confirmación con pulsación prolongada (hold): Se optó por implementar una barra de progreso que requiere mantener pulsado el botón antes de confirmar el desbloqueo. Esto evita desbloqueos accidentales y aporta un feedback visual claro.</li>
 <li>Sistema de dependencias: En lugar de codificar manualmente qué habilidades dependen de otras, se decidió usar identificadores (FName) configurables en el editor. Luego, en USkillTreeWidget, se resuelven dinámicamente las referencias. Esto mejora la escalabilidad y la flexibilidad del sistema.</li>
 <li>Uso de estilos de botón (FButtonStyle): Se decidió modificar directamente los brushes del botón para representar los distintos estados (normal, hovered, pressed) con iconos distintos. Así, el jugador recibe un feedback visual inmediato al desbloquear una habilidad.</li>
 <li>Sistema de notificaciones: En lugar de mensajes de depuración únicamente (GEngine->AddOnScreenDebugMessage), se implementó un widget (UNotificationWidget) para mostrar mensajes dentro de la interfaz de usuario. Esto es más intuitivo y profesional.</li>
</ul>

<h2 align="center"> Conclusiones </h2>
La implementación lograda permite un sistema modular y escalable de habilidades, con validaciones de dependencias, consumo de puntos, notificaciones y un flujo de interacción claro. Las decisiones tomadas han buscado un equilibrio entre usabilidad (confirmación por pulsación prolongada, notificaciones claras) y flexibilidad (dependencias configurables en el editor, estilos de botones dinámicos).
