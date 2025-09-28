# UTAD-UI-FPS-Public

<h1 align="center"> Práctica sobre interfaces: Creación de un árbol de habilidades. </h1>

<p align="center">
  <b>Universidad U-Tad· Asignatura: Interfaces</b><br>
  <i>Implementación de un sistema de árbol de habilidades con dependencias y desbloqueo progresivo.</i>
</p>

El propósito de esta actividad fue implementar un sistema de árbol de habilidades (Skill Tree) en Unreal Engine, donde cada habilidad (Skill) puede estar condicionada por otras previas y requiere la interacción del jugador para que sean desbloqueadas a base de consumir puntos.

Su implementación fue realizada de la siguiente manera:

<h2 align="center"> 1. USkillWidget Class </h2>
Esta clase representa una habilidad individual dentro del árbol. Sus principales funciones son:

<h3> NativeConstruct (Inicialización) </h3>
<ul>
  <li>Obtiene una referencia al personaje (AUTAD_UI_FPSCharacter) para acceder a los puntos disponibles del jugador.</li>
  <li>Se configura el estilo visual del botón (FButtonStyle) para mostrar el icono correspondiente a la habilidad dependiendo de si esta está bloqueada o desbloqueada.</li>
  <li>Se configuran las funciones de lo que ocurre si se pulsa el botón:
    <ul>
      <li>OnButtonPressed: Valida si el jugador tiene puntos suficientes, si la habilidad ya está desbloqueada y si las habilidades previas requeridas lo están. En caso negativo, se muestra un mensaje de notificación.</li>
      <li>OnButtonReleased: Cancela la acción si el jugador no mantiene la pulsación el tiempo suficiente.</li>
    </ul>
  </li>
  <li>Se inicializa la barra de confirmación (ProgressBar_Confirm) en estado oculto.</li>
  <li>Se establecen los puntos que tiene el jugador en el momento.</li>
</ul>

<h3> NativeTick: </h3>
<ul>
  <li>Gestiona el tiempo de pulsación (hold). Al completarse el tiempo requerido, se confirma el desbloqueo llamando a la función OnButtonClicked.</li>
</ul>

<h3> OnButtonClicked: </h3>
<ul>
  <li>Marca la habilidad como desbloqueada y activa los cambios visuales y lógicos correspondientes. Por la parte visual se llama a la función de UnlockSkill y por la parte de habilidad se llama a la función de UnlockAbility. (Como de momento no hay habilidades esta función no hace nada, a futuro sería la encargada de esto.)</li>
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
Esta clase es la que representa el contenedor de todo el árbol de habilidades. Sus funciones principales son:

<h3> NativeConstruct: </h3>
<ul>
 <li>Recorre el CanvasPanel para recoger todas las instancias de USkillWidget.</li>
 <li>Genera un mapa (SkillMap) que relaciona el SkillID con su widget correspondiente.</li>
 <li>Rellena las referencias de dependencias (m_pPreviousSkills) en cada widget, en función de los identificadores declarados en el editor (m_PreviousSkillIDs).</li>
</ul>

<h3> NativeOnMouseButtonDown (Entrada de usuario): </h3>
<ul>
  <li>Devuelve un FReply::Handled para evitar interacciones no deseadas en el lienzo.</li>
</ul>

<h2 align="center"> Decisiones de diseño </h2>
<ul>
 <li>Hacer una Confirmación con pulsación prolongada en los botones: Se optó por implementar una barra de progreso que requiere mantener pulsado el botón antes de confirmar el desbloqueo para evitar desbloqueos accidentales y poder tener también ese ffeedback visual al pulsar el botón. Podría haberse escogido crear una ventana de confirmación, pero personalmente veía que esta opción era más elegante y limpia.</li>
 <li>Sistema de dependencias: En lugar de codificar manualmente qué habilidades dependen de otras, se decidió usar identificadores (FName) configurables en el editor. Luego, en USkillTreeWidget, se resuelven dinámicamente estas referencias, mejorando la escalabilidad y la flexibilidad del sistema.</li>
 <li>Uso de estilos de botón (FButtonStyle): Se decidió modificar directamente los brushes del botón para representar los distintos estados (normal, hovered, pressed) con iconos distintos. Así, el jugador recibe un feedback visual inmediato al desbloquear una habilidad, ya que de otra manera la interfaz llegaría a ser muy confusa.</li>
 <li>Sistema de notificaciones: En lugar de mensajes de depuración únicamente (GEngine->AddOnScreenDebugMessage), se implementó un widget (UNotificationWidget) para mostrar mensajes dentro de la interfaz de usuario. Esto es más intuitivo y profesional. El widget acabó siendo muy básico debido a la falta de tiempo, a futuro la estética de este estaría diseñada para que concuerde con la del propio árbol de habilidades.</li>
</ul>

<h2 align="center"> Conclusiones </h2>
La implementación creada permite un sistema modular y escalable de habilidades, con validaciones de dependencias, consumo de puntos, notificaciones y un flujo de interacción claro. Las decisiones tomadas han buscado un equilibrio entre usabilidad (confirmación por pulsación prolongada, notificaciones claras) y flexibilidad (dependencias configurables en el editor, estilos de botones dinámicos).
