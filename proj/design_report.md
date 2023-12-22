# Design Report

In the file proj/design_report.md, describe the design of the system at a high level. The purpose of this document is to serve as a starting point for someone that wants to understand the implementation. You must also describe all deviations from the full specification. For every feature X that you do not deliver, explain why you do not deliver it, how the feature could be integrated in the future in your system, and sketch the high-level design.

Together with the actual code, this file will be used by the examiner to convince him/herself that you pass Y68.


Är det här vi ska skrive ex. att vi har en extra hjälp function "get_meta_deta()" och varför vi la till den?
    (Hade kunnat ha static och på så sätt ej ändra h-file men vi använder även i tests.c så måste vara public)