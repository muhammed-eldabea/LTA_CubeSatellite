# LTA_CubeSatellite
a small prototype for cube-satellite have two Sub-system (OBC-Control)  

![CubeSat](https://directory.eoportal.org/documents/163813/3328251/OUFTI1_AutoD.jpeg)


LTA project definition ..

 الهدف من البروجكت أننا نعمل سيمويلشن للقمر الصناعي والهدف الأكبر أننا كمان نشوف ال obc 
وال فنشكنلتي بتاعته اللي هي command handling and data gathering  علشان كدا كان لازم نغير ف المشروع ونستخدم بوردتين علشان نقدر نشوف بعنينا ونلمس موضوع modularity  ونشوف ازاي الفانكشن لل obc بتحصل .. 
 هتشوفوا اتنين اردوينو واحد بيمثل obc والتاني بيمثل ال control  وفي معنا بلوتوث موديل بيمثل لينا ground station  تقدر من خلال الابليكشن دا تتحكم ف كل تاسك بيقدر يعملها البروتوتيب اللي معانا .. من initial mode .. or communication or imaging or download modes ... 
او انك تشغل مود automatic  وهو بيعمل كل التاسكات لوحده .. 
ولو عايز كمان نتست ال faluiar mode  اللي تقدر ب بوتن معين نعمل الخطوه دي .. 
ف حاجه زي indicator لكل تاسك ف مقدمة النموذج عباره عن ليد بتنور كل ما تاسك تخلص و ف اسفل النموذج ف ليد بيمثل ال payload اللي ممكن يبقي كاميرا أو سينسور ودا بيعتمد علي الهدف من القمر . ف وضع ال download  كل ال ليدات بيحصل ليها iterative blink 
ال faluiar mode  المفروض أن كل فتره انا ببعت synchronization signal  ومتوقع أن ال control  هيرد عليا لو مردش كدا ف faluiar حصل وهبعت reset signal l module ..   
الجزء الأساسي اللي خلانا نستخدم نستخدم حاجه زي RTOS  اني مش عايز تعطل البروسيسور لما اعمل synchronization signal انا ف الحقيقه مش ب wait لكن  بعمل حاحات تاني مع subsystem تانيه وبعد وقت محسوب ارجع وأشوف  synchronization signal دي ايه اخبارها ... والدور الثاني أنه كمان بيقدر يهندل ال inter connection  بين التاسكات  .. مثال .. 
المفروض أن فيه فلاج بيترفع لو synchronization signal دي مجتش ف المفروض أن كل التاسكات تقدر ت access الفلاج دا بس مش كلهم يقدروا يعملوا الخطوه دي ف نفس الوقت علشان كدا ال RTOS  بيقدم حاجه اسمها semaphore and mutux دا بيخلينا تتحكم في ال shared resources .. 
Source Code is available here  : 
demo link 
https://www.facebook.com/MEKANOS125/videos/3408761889214565
 
