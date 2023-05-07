import 'package:flutter/material.dart';
import 'package:matdis_control/application/advicer/advicer_bloc.dart';
import 'package:flutter_bloc/flutter_bloc.dart';

class CustomPointsFieldHorizontal extends StatelessWidget {
  const CustomPointsFieldHorizontal({super.key});

  @override
  Widget build(BuildContext context) {
    final themeData = Theme.of(context);

    return InkResponse(
      // onTap: () =>
      //     BlocProvider.of<AdvicerBloc>(context).add(AdviceRequestedEvent()),
      child: Stack(
        clipBehavior: Clip.none,
        // overflow: Overflow.visible,
        children: [
          Card(
            elevation: 1,
            color: Colors.blue,
            child: Container(
                width: 120,
                height: 120,
                child: const Center(
                  child: Text(
                    "00",
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 50,
                        fontWeight: FontWeight.normal),
                  ),
                )),
          ),
          const Positioned(
              top: 30,
              left: -40,
              child: Card(
                elevation: 3,
                color: Colors.white54,
                child: SizedBox(
                  width: 60,
                  height: 60,
                  child: Center(
                    child: Icon(
                      Icons.remove,
                      color: Colors.white,
                      size: 40,
                    ),
                  ),
                ),
              )),
          const Positioned(
            top: 30,
            right: -40,
            child: Card(
              elevation: 3,
              color: Colors.white70,
              child: SizedBox(
                width: 60,
                height: 60,
                child: Center(
                  child: Icon(
                    Icons.add,
                    color: Colors.white,
                    size: 40,
                  ),
                ),
              ),
            ),
          )
        ],
      ),
    );
  }
}
